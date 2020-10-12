#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET   //小爱同学
#include <Blinker.h>

char auth[] = "85f4159c24c2";
char ssid[] = "WWW_Home";
char pswd[] = "671682551";

// 新建组件对象
BlinkerButton Button1("btn-on");     //定义按钮数据
BlinkerButton Button2("btn-kg"); 
bool oState = false;
bool kg = true;
unsigned long time_1 = 120000;
unsigned long time_2 = 600000;
char id = D0;
String zzz="on";
unsigned long millistime = millis();
// 按下按键即会执行该函数
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {     //小爱同学控制开命令
        digitalWrite(id, HIGH);

        BlinkerMIOT.powerState("on");

        BlinkerMIOT.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) {   //小爱同学控制关命令
        digitalWrite(id,LOW);

        BlinkerMIOT.powerState("off");

        BlinkerMIOT.print();

        oState = false;
    }
}

void miotQuery(int32_t queryCode)      //小爱同学控制
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("MIOT Query All");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("MIOT Query Power State");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
    }
}
void button1_callback(const String & state) {//开关模式
    BLINKER_LOG("get button state: ", state);
    if (state=="on") {
        digitalWrite(id, HIGH);
        // 反馈开关状态
        Button1.print("on");
    } else{
        digitalWrite(id, LOW);
        // 反馈开关状态
        Button1.print("off");
    }
}

void button2_callback(const String & state)     //点灯app内控制按键触发,完全打开或者关闭，永久
{
    
    if (state=="on") {
        kg=true;
        // 反馈开关状态
        Button2.print("on");
    } else{
        kg=false;
        // 反馈开关状态
        Button2.print("off");
    }
    BLINKER_LOG("get button state:off", state);


}
/*
void button1_callback(const String & state)     //点灯app内控制按键触发
{
    
    digitalWrite(id,HIGH);
    BLINKER_LOG("get button state:on", state);


}
void button2_callback(const String & state)     //点灯app内控制按键触发
{
    
    digitalWrite(id,LOW);
    BLINKER_LOG("get button state:off", state);


}
*/

void ds(bool inkg){
  if(inkg==true){
  
    if(millistime > time_1){
        time_1 = 600000+millistime;
        
        digitalWrite(id,LOW);
    }
    if(millistime > time_2){
        time_2 = 600000+millistime;
        
        digitalWrite(id, HIGH);
    }}
  }
void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    
    // 初始化有LED的IO
    pinMode(id, OUTPUT);              //定义io口为输出
    digitalWrite(id, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);

BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
   Button1.attach(button1_callback);  
    Button2.attach(button2_callback); 
   Button2.print("on");
       
}

void loop() {
  millistime = millis();
     ds(kg);
    Blinker.run();
    if(digitalRead(id))
    {zzz="on";}
    else
    {zzz="off";}
Button1.print((String)zzz);
    
    Blinker.delay(1000);

}

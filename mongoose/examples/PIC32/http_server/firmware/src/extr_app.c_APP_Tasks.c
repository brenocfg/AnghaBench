#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mg_connection {int dummy; } ;
struct TYPE_6__ {int state; } ;
struct TYPE_5__ {int /*<<< orphan*/  tcpip; } ;
struct TYPE_4__ {int member_0; int* v; int /*<<< orphan*/  Val; } ;
typedef  int /*<<< orphan*/  TCPIP_NET_HANDLE ;
typedef  int /*<<< orphan*/  SYS_STATUS ;
typedef  TYPE_1__ IPV4_ADDR ;

/* Variables and functions */
#define  APP_DONE 133 
#define  APP_EMPTY 132 
#define  APP_POLL 131 
#define  APP_START_LISTENING 130 
#define  APP_STATE_INIT 129 
#define  APP_TCPIP_WAIT_FOR_IP 128 
 int /*<<< orphan*/  SYS_CONSOLE_MESSAGE (char*) ; 
 int /*<<< orphan*/  SYS_CONSOLE_PRINT (char*,...) ; 
 int /*<<< orphan*/  SYS_STATUS_READY ; 
 int /*<<< orphan*/  TCPIP_STACK_IndexToNet (int) ; 
 int /*<<< orphan*/  TCPIP_STACK_NetAddress (int /*<<< orphan*/ ) ; 
 char* TCPIP_STACK_NetBIOSName (int /*<<< orphan*/ ) ; 
 char* TCPIP_STACK_NetNameGet (int /*<<< orphan*/ ) ; 
 int TCPIP_STACK_NumberOfNetworksGet () ; 
 int /*<<< orphan*/  TCPIP_STACK_Status (int /*<<< orphan*/ ) ; 
 TYPE_3__ appData ; 
 int /*<<< orphan*/  ev_handler ; 
 struct mg_connection* mg_bind (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_poll (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  mgr ; 
 TYPE_2__ sysObj ; 

void APP_Tasks ( void )
{
    SYS_STATUS          tcpipStat;
    const char          *netName, *netBiosName;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    TCPIP_NET_HANDLE    netH;
    int                 i, nNets;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                SYS_CONSOLE_MESSAGE(" APP: TCP/IP stack initialization failed!\r\n");
                appData.state = APP_DONE;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                // now that the stack is ready we can check the
                // available interfaces
                nNets = TCPIP_STACK_NumberOfNetworksGet();
                for(i = 0; i < nNets; i++)
                {

                    netH = TCPIP_STACK_IndexToNet(i);
                    netName = TCPIP_STACK_NetNameGet(netH);
                    netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif  // defined(TCPIP_STACK_USE_NBNS)

                }
                appData.state = APP_TCPIP_WAIT_FOR_IP;

            }
            break;
        }
        case APP_TCPIP_WAIT_FOR_IP:

            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                    if (ipAddr.v[0] != 0 && ipAddr.v[0] != 169) // Wait for a Valid IP
                    {
                        appData.state = APP_START_LISTENING;
                    }
                }
            }
            break;
        case APP_START_LISTENING:
        {
            SYS_CONSOLE_PRINT("Starting listening on port 8000\r\n");
            struct mg_connection *nc = mg_bind(&mgr, "8000", ev_handler);  // Create listening connection and add it to the event manager
            if (nc == NULL) {
              SYS_CONSOLE_PRINT("Failed to create listener\n\r");
              appData.state = APP_DONE;
              break;
            }
            mg_set_protocol_http_websocket(nc);
            SYS_CONSOLE_PRINT("Listener started\r\n");

            appData.state = APP_POLL;
            break;
        }
        case APP_POLL:
        {
            mg_mgr_poll(&mgr, 1000);
            break;
        }
        case APP_DONE:
        {
            SYS_CONSOLE_PRINT("Server stopped\n\r");
            appData.state = APP_EMPTY;
            break;
        }
        case APP_EMPTY:
        {
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
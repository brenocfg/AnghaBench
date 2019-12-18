#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int Event; } ;
typedef  TYPE_1__ SlNetAppEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_STATE_CONNECT_BROKER ; 
#define  SL_NETAPP_IPV4_IPACQUIRED_EVENT 128 
 int /*<<< orphan*/  SYS_PRINT (char*,...) ; 
 TYPE_2__ appData ; 

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent) {
  switch (pNetAppEvent->Event) {
    case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
      SYS_PRINT("Got IP\r\n");
      appData.state = APP_STATE_CONNECT_BROKER;
      break;
    default:
      SYS_PRINT("Got NetApp Event: %d\r\n", pNetAppEvent->Event);
      break;
  }
}
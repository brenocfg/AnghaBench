#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Event; } ;
typedef  TYPE_1__ SlWlanEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLI_Write (char*,...) ; 
#define  SL_WLAN_CONNECT_EVENT 129 
#define  SL_WLAN_DISCONNECT_EVENT 128 

void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent) {
  switch (pWlanEvent->Event) {
    case SL_WLAN_CONNECT_EVENT:
      CLI_Write("Connected to WiFi\r\n");
      break;
    case SL_WLAN_DISCONNECT_EVENT:
      CLI_Write("Disconnected WiFi\r\n");
      break;
    default:
      CLI_Write("Got Wlan event %d\r\n", pWlanEvent->Event);
      break;
  }
}
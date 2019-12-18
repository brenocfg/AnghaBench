#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_6__ {int /*<<< orphan*/  os_event; } ;
typedef  TYPE_1__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DeInitStateMachine (TYPE_1__*) ; 
 int /*<<< orphan*/  USBH_Delay (int) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PORT_EVENT ; 
 int /*<<< orphan*/  USBH_Start (TYPE_1__*) ; 
 int /*<<< orphan*/  USBH_Stop (TYPE_1__*) ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef  USBH_ReEnumerate   (USBH_HandleTypeDef *phost)
{
  /*Stop Host */ 
  USBH_Stop(phost);

  /*Device has disconnected, so wait for 200 ms */  
  USBH_Delay(200);
  
  /* Set State machines in default state */
  DeInitStateMachine(phost);
   
  /* Start again the host */
  USBH_Start(phost);
      
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
#endif  
  return USBH_OK;  
}
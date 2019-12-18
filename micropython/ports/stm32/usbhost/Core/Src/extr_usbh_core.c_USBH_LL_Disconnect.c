#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_10__ {scalar_t__ is_connected; } ;
struct TYPE_9__ {int /*<<< orphan*/  pipe_out; int /*<<< orphan*/  pipe_in; } ;
struct TYPE_11__ {int /*<<< orphan*/  os_event; int /*<<< orphan*/  gState; int /*<<< orphan*/  (* pUser ) (TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_2__ device; TYPE_1__ Control; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_DEV_DISCONNECTED ; 
 int /*<<< orphan*/  HOST_USER_DISCONNECTION ; 
 int /*<<< orphan*/  USBH_FreePipe (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_Start (TYPE_3__*) ; 
 int /*<<< orphan*/  USBH_LL_Stop (TYPE_3__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PORT_EVENT ; 
 int /*<<< orphan*/  USBH_UsrLog (char*) ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef  USBH_LL_Disconnect  (USBH_HandleTypeDef *phost)
{
  /*Stop Host */ 
  USBH_LL_Stop(phost);  
  
  /* FRee Control Pipes */
  USBH_FreePipe  (phost, phost->Control.pipe_in);
  USBH_FreePipe  (phost, phost->Control.pipe_out);  
   
  phost->device.is_connected = 0; 
   
  if(phost->pUser != NULL)
  {    
    phost->pUser(phost, HOST_USER_DISCONNECTION);
  }
  USBH_UsrLog("USB Device disconnected"); 
  
  /* Start the low level driver  */
  USBH_LL_Start(phost);
  
  phost->gState = HOST_DEV_DISCONNECTED;
  
#if (USBH_USE_OS == 1)
  osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
#endif 
  
  return USBH_OK;
}
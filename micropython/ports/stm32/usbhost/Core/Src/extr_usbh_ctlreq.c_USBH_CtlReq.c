#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  length; int /*<<< orphan*/ * buff; } ;
struct TYPE_6__ {int RequestState; TYPE_1__ Control; int /*<<< orphan*/  os_event; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;

/* Variables and functions */
#define  CMD_SEND 129 
#define  CMD_WAIT 128 
 int /*<<< orphan*/  CTRL_IDLE ; 
 int /*<<< orphan*/  CTRL_SETUP ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_CONTROL_EVENT ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_HandleControl (TYPE_2__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef USBH_CtlReq     (USBH_HandleTypeDef *phost, 
                             uint8_t             *buff,
                             uint16_t            length)
{
  USBH_StatusTypeDef status;
  status = USBH_BUSY;
  
  switch (phost->RequestState)
  {
  case CMD_SEND:
    /* Start a SETUP transfer */
    phost->Control.buff = buff; 
    phost->Control.length = length;
    phost->Control.state = CTRL_SETUP;  
    phost->RequestState = CMD_WAIT;
    status = USBH_BUSY;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    break;
    
  case CMD_WAIT:
    status = USBH_HandleControl(phost);
     if (status == USBH_OK) 
    {
      /* Commands successfully sent and Response Received  */       
      phost->RequestState = CMD_SEND;
      phost->Control.state =CTRL_IDLE;  
      status = USBH_OK;      
    }
    else if  (status == USBH_FAIL)
    {
      /* Failure Mode */
      phost->RequestState = CMD_SEND;
      status = USBH_FAIL;
    }   
    break;
    
  default:
    break; 
  }
  return status;
}
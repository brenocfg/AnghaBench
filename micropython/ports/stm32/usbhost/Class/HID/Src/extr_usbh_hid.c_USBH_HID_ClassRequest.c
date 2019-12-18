#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {int /*<<< orphan*/  Data; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* pUser ) (TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_2__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_16__ {int /*<<< orphan*/  wItemLength; } ;
struct TYPE_15__ {int ctl_state; TYPE_8__ HID_Desc; } ;
struct TYPE_12__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ HID_HandleTypeDef ;

/* Variables and functions */
#define  HID_REQ_GET_HID_DESC 133 
#define  HID_REQ_GET_REPORT_DESC 132 
#define  HID_REQ_IDLE 131 
#define  HID_REQ_INIT 130 
#define  HID_REQ_SET_IDLE 129 
#define  HID_REQ_SET_PROTOCOL 128 
 int /*<<< orphan*/  HOST_USER_CLASS_ACTIVE ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_HID_GetHIDDescriptor (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_HID_GetHIDReportDescriptor (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_HID_ParseHIDDesc (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_HID_SetIdle (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_HID_SetProtocol (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_NOT_SUPPORTED ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USB_HID_DESC_SIZE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HID_ClassRequest(USBH_HandleTypeDef *phost)
{   
  
  USBH_StatusTypeDef status         = USBH_BUSY;
  USBH_StatusTypeDef classReqStatus = USBH_BUSY;
  HID_HandleTypeDef *HID_Handle =  phost->pActiveClass->pData; 

  /* Switch HID state machine */
  switch (HID_Handle->ctl_state)
  {
  case HID_REQ_INIT:  
  case HID_REQ_GET_HID_DESC:
    
    /* Get HID Desc */ 
    if (USBH_HID_GetHIDDescriptor (phost, USB_HID_DESC_SIZE)== USBH_OK)
    {
      
      USBH_HID_ParseHIDDesc(&HID_Handle->HID_Desc, phost->device.Data);
      HID_Handle->ctl_state = HID_REQ_GET_REPORT_DESC;
    }
    
    break;     
  case HID_REQ_GET_REPORT_DESC:
    
    
    /* Get Report Desc */ 
    if (USBH_HID_GetHIDReportDescriptor(phost, HID_Handle->HID_Desc.wItemLength) == USBH_OK)
    {
      /* The decriptor is available in phost->device.Data */

      HID_Handle->ctl_state = HID_REQ_SET_IDLE;
    }
    
    break;
    
  case HID_REQ_SET_IDLE:
    
    classReqStatus = USBH_HID_SetIdle (phost, 0, 0);
    
    /* set Idle */
    if (classReqStatus == USBH_OK)
    {
      HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;  
    }
    else if(classReqStatus == USBH_NOT_SUPPORTED) 
    {
      HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;        
    } 
    break; 
    
  case HID_REQ_SET_PROTOCOL:
    /* set protocol */
    if (USBH_HID_SetProtocol (phost, 0) == USBH_OK)
    {
      HID_Handle->ctl_state = HID_REQ_IDLE;
      
      /* all requests performed*/
      phost->pUser(phost, HOST_USER_CLASS_ACTIVE); 
      status = USBH_OK; 
    } 
    break;
    
  case HID_REQ_IDLE:
  default:
    break;
  }
  
  return status; 
}
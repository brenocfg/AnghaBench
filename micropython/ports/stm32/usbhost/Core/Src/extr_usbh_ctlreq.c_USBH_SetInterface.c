#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {scalar_t__ w; } ;
struct TYPE_11__ {void* w; } ;
struct TYPE_10__ {void* w; } ;
struct TYPE_15__ {int bmRequestType; TYPE_3__ wLength; TYPE_2__ wIndex; TYPE_1__ wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_13__ {TYPE_6__ b; } ;
struct TYPE_14__ {TYPE_4__ setup; } ;
struct TYPE_16__ {scalar_t__ RequestState; TYPE_5__ Control; } ;
typedef  TYPE_7__ USBH_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ CMD_SEND ; 
 int /*<<< orphan*/  USBH_CtlReq (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USB_H2D ; 
 int USB_REQ_RECIPIENT_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_SET_INTERFACE ; 
 int USB_REQ_TYPE_STANDARD ; 

USBH_StatusTypeDef USBH_SetInterface(USBH_HandleTypeDef *phost, 
                        uint8_t ep_num, uint8_t altSetting)
{
  
  if(phost->RequestState == CMD_SEND)
  {
    phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | \
      USB_REQ_TYPE_STANDARD;
    
    phost->Control.setup.b.bRequest = USB_REQ_SET_INTERFACE;
    phost->Control.setup.b.wValue.w = altSetting;
    phost->Control.setup.b.wIndex.w = ep_num;
    phost->Control.setup.b.wLength.w = 0;           
  }
  return USBH_CtlReq(phost, 0 , 0 );     
}
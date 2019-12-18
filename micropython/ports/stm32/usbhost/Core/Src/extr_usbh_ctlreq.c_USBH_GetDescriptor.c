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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {int w; } ;
struct TYPE_11__ {int w; } ;
struct TYPE_10__ {int w; } ;
struct TYPE_13__ {int bmRequestType; TYPE_3__ wLength; TYPE_2__ wIndex; TYPE_1__ wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_14__ {TYPE_4__ b; } ;
struct TYPE_15__ {TYPE_5__ setup; } ;
struct TYPE_16__ {scalar_t__ RequestState; TYPE_6__ Control; } ;
typedef  TYPE_7__ USBH_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ CMD_SEND ; 
 int /*<<< orphan*/  USBH_CtlReq (TYPE_7__*,int*,int) ; 
 int USB_D2H ; 
 int USB_DESC_STRING ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 

USBH_StatusTypeDef USBH_GetDescriptor(USBH_HandleTypeDef *phost,                          
                               uint8_t  req_type,
                               uint16_t value_idx, 
                               uint8_t* buff, 
                               uint16_t length )
{ 
  if(phost->RequestState == CMD_SEND)
  {
    phost->Control.setup.b.bmRequestType = USB_D2H | req_type;
    phost->Control.setup.b.bRequest = USB_REQ_GET_DESCRIPTOR;
    phost->Control.setup.b.wValue.w = value_idx;
    
    if ((value_idx & 0xff00) == USB_DESC_STRING)
    {
      phost->Control.setup.b.wIndex.w = 0x0409;
    }
    else
    {
      phost->Control.setup.b.wIndex.w = 0;
    }
    phost->Control.setup.b.wLength.w = length; 
  }
  return USBH_CtlReq(phost, buff , length );     
}
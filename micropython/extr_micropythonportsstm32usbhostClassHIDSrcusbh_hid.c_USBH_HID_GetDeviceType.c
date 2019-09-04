#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* Itf_Desc; } ;
struct TYPE_7__ {size_t current_interface; TYPE_3__ CfgDesc; } ;
struct TYPE_9__ {scalar_t__ gState; TYPE_2__ device; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_6__ {scalar_t__ bInterfaceProtocol; } ;
typedef  int /*<<< orphan*/  HID_TypeTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HID_KEYBOARD ; 
 scalar_t__ HID_KEYBRD_BOOT_CODE ; 
 int /*<<< orphan*/  HID_MOUSE ; 
 scalar_t__ HID_MOUSE_BOOT_CODE ; 
 int /*<<< orphan*/  HID_UNKNOWN ; 
 scalar_t__ HOST_CLASS ; 

HID_TypeTypeDef USBH_HID_GetDeviceType(USBH_HandleTypeDef *phost)
{
  HID_TypeTypeDef   type = HID_UNKNOWN;
  
  if(phost->gState == HOST_CLASS)
  {
    
    if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol \
      == HID_KEYBRD_BOOT_CODE)
    {
      type = HID_KEYBOARD;  
    }
    else if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol \
      == HID_MOUSE_BOOT_CODE)		  
    {
      type=  HID_MOUSE;  
    }
  }
  return type;
}
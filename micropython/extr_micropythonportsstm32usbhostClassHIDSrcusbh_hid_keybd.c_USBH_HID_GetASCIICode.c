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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int lshift; size_t* keys; scalar_t__ rshift; } ;
typedef  TYPE_1__ HID_KEYBD_Info_TypeDef ;

/* Variables and functions */
 size_t* HID_KEYBRD_Codes ; 
 int /*<<< orphan*/ * HID_KEYBRD_Key ; 
 int /*<<< orphan*/ * HID_KEYBRD_ShiftKey ; 

uint8_t USBH_HID_GetASCIICode(HID_KEYBD_Info_TypeDef *info)
{
  uint8_t   output;  
  if((info->lshift == 1) || (info->rshift))
  {
  output =  HID_KEYBRD_ShiftKey[HID_KEYBRD_Codes[info->keys[0]]];
  }
  else
  {
  output =  HID_KEYBRD_Key[HID_KEYBRD_Codes[info->keys[0]]];
  }
  return output;  
}
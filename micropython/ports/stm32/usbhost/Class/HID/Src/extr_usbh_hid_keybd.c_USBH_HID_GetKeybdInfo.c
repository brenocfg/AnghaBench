#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_HandleTypeDef ;
typedef  int /*<<< orphan*/  HID_KEYBD_Info_TypeDef ;

/* Variables and functions */
 scalar_t__ USBH_HID_KeybdDecode (int /*<<< orphan*/ *) ; 
 scalar_t__ USBH_OK ; 
 int /*<<< orphan*/  keybd_info ; 

HID_KEYBD_Info_TypeDef *USBH_HID_GetKeybdInfo(USBH_HandleTypeDef *phost)
{
  if(USBH_HID_KeybdDecode(phost) == USBH_OK)
 {
  return &keybd_info;
 }
 else
 {
  return NULL; 
 }  
}
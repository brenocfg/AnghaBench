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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_9__ {int lctrl; int lshift; int lalt; int lgui; int rctrl; int rshift; int ralt; int rgui; int* keys; } ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/  fifo; } ;
struct TYPE_6__ {TYPE_3__* pData; } ;
typedef  int /*<<< orphan*/  HID_Report_ItemTypedef ;
typedef  TYPE_3__ HID_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HID_ReadItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 
 scalar_t__ fifo_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  imp_0_key_array ; 
 int /*<<< orphan*/  imp_0_lalt ; 
 int /*<<< orphan*/  imp_0_lctrl ; 
 int /*<<< orphan*/  imp_0_lgui ; 
 int /*<<< orphan*/  imp_0_lshift ; 
 int /*<<< orphan*/  imp_0_ralt ; 
 int /*<<< orphan*/  imp_0_rctrl ; 
 int /*<<< orphan*/  imp_0_rgui ; 
 int /*<<< orphan*/  imp_0_rshift ; 
 TYPE_4__ keybd_info ; 
 int /*<<< orphan*/  keybd_report_data ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HID_KeybdDecode(USBH_HandleTypeDef *phost)
{
  uint8_t x;
  
  HID_HandleTypeDef *HID_Handle =  phost->pActiveClass->pData;
  if(HID_Handle->length == 0)
  {
    return USBH_FAIL;
  }
  /*Fill report */
  if(fifo_read(&HID_Handle->fifo, &keybd_report_data, HID_Handle->length) ==  HID_Handle->length)
  {
    
    keybd_info.lctrl=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_lctrl, 0);
    keybd_info.lshift=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_lshift, 0);
    keybd_info.lalt=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_lalt, 0);
    keybd_info.lgui=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_lgui, 0);
    keybd_info.rctrl=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_rctrl, 0);
    keybd_info.rshift=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_rshift, 0);
    keybd_info.ralt=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_ralt, 0);
    keybd_info.rgui=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_rgui, 0);
    
    for(x=0; x < sizeof(keybd_info.keys); x++)
    {    
      keybd_info.keys[x]=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &imp_0_key_array, x);
    }
    
    return USBH_OK; 
  }
  return   USBH_FAIL;  
}
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
typedef  void* uint8_t ;
typedef  void* int16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_9__ {void** buttons; void* y; void* x; } ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/  fifo; } ;
struct TYPE_6__ {TYPE_3__* pData; } ;
typedef  int /*<<< orphan*/  HID_Report_ItemTypedef ;
typedef  TYPE_3__ HID_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HID_ReadItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 
 scalar_t__ fifo_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__ mouse_info ; 
 int /*<<< orphan*/  mouse_report_data ; 
 int /*<<< orphan*/  prop_b1 ; 
 int /*<<< orphan*/  prop_b2 ; 
 int /*<<< orphan*/  prop_b3 ; 
 int /*<<< orphan*/  prop_x ; 
 int /*<<< orphan*/  prop_y ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HID_MouseDecode(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  phost->pActiveClass->pData;
  
  if(HID_Handle->length == 0)
  {
    return USBH_FAIL;
  }
  /*Fill report */
  if(fifo_read(&HID_Handle->fifo, &mouse_report_data, HID_Handle->length) ==  HID_Handle->length)
  {
    
    /*Decode report */
    mouse_info.x = (int16_t )HID_ReadItem((HID_Report_ItemTypedef *) &prop_x, 0);
    mouse_info.y = (int16_t )HID_ReadItem((HID_Report_ItemTypedef *) &prop_y, 0);
    
    mouse_info.buttons[0]=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_b1, 0);
    mouse_info.buttons[1]=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_b2, 0);
    mouse_info.buttons[2]=(uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_b3, 0);
    
    return USBH_OK;  
  }
  return   USBH_FAIL;
}
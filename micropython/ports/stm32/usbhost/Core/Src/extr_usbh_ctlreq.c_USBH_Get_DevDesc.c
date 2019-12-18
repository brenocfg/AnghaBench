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
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  DevDesc; } ;
struct TYPE_6__ {TYPE_1__ device; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_GetDescriptor (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_ParseDevDesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_DESC_DEVICE ; 
 int USB_REQ_RECIPIENT_DEVICE ; 
 int USB_REQ_TYPE_STANDARD ; 

USBH_StatusTypeDef USBH_Get_DevDesc(USBH_HandleTypeDef *phost, uint8_t length)
{
  USBH_StatusTypeDef status;
  
  if((status = USBH_GetDescriptor(phost,
                                  USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD,                          
                                  USB_DESC_DEVICE, 
                                  phost->device.Data,
                                  length)) == USBH_OK)
  {
    /* Commands successfully sent and Response Received */       
    USBH_ParseDevDesc(&phost->device.DevDesc, phost->device.Data, length);
  }
  return status;      
}
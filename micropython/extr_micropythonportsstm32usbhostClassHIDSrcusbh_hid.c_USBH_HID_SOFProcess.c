#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_6__ {scalar_t__ Timer; TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ timer; scalar_t__ poll; } ;
struct TYPE_5__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ HID_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HID_GET_DATA ; 
 scalar_t__ HID_POLL ; 
 int /*<<< orphan*/  USBH_OK ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HID_SOFProcess(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  phost->pActiveClass->pData;
  
  if(HID_Handle->state == HID_POLL)
  {
    if(( phost->Timer - HID_Handle->timer) >= HID_Handle->poll)
    {
      HID_Handle->state = HID_GET_DATA;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
  }
  return USBH_OK;
}
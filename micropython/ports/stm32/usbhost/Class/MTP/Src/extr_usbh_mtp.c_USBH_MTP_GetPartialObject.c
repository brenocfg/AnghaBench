#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {scalar_t__ is_connected; } ;
struct TYPE_9__ {scalar_t__ Timer; TYPE_1__ device; TYPE_2__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ is_ready; } ;
struct TYPE_8__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_PTP_GetPartialObject (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

USBH_StatusTypeDef USBH_MTP_GetPartialObject(USBH_HandleTypeDef *phost, 
                                           uint32_t handle, 
                                           uint32_t offset,
                                           uint32_t maxbytes, 
                                           uint8_t *object,
                                           uint32_t *len)
{
  USBH_StatusTypeDef status = USBH_FAIL;
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData;
  uint32_t timeout = phost->Timer + 5000;
  
  if(MTP_Handle->is_ready)
  {   
    while ((status = USBH_PTP_GetPartialObject(phost, 
                                           handle, 
                                           offset,
                                           maxbytes, 
                                           object,
                                           len)) == USBH_BUSY)
    {
      if((phost->Timer > timeout) || (phost->device.is_connected == 0)) 
      {
        return USBH_FAIL;
      }
    }
  }
  return status;
}
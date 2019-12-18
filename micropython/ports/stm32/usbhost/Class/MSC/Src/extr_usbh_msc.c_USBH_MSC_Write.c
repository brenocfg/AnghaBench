#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_11__ {scalar_t__ is_connected; } ;
struct TYPE_12__ {scalar_t__ gState; int Timer; TYPE_3__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_13__ {size_t rw_lun; void* state; TYPE_2__* unit; } ;
struct TYPE_10__ {scalar_t__ state; } ;
struct TYPE_9__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ MSC_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HOST_CLASS ; 
 scalar_t__ MSC_IDLE ; 
 void* MSC_WRITE ; 
 scalar_t__ USBH_BUSY ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 scalar_t__ USBH_MSC_RdWrProcess (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  USBH_MSC_SCSI_Write (TYPE_4__*,size_t,int,size_t*,int) ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_MSC_Write(USBH_HandleTypeDef *phost,
                                     uint8_t lun,
                                     uint32_t address,
                                     uint8_t *pbuf,
                                     uint32_t length)
{
  uint32_t timeout;
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;   
  
  if ((phost->device.is_connected == 0) || 
      (phost->gState != HOST_CLASS) || 
      (MSC_Handle->unit[lun].state != MSC_IDLE))
  {
    return  USBH_FAIL;
  }
  MSC_Handle->state = MSC_WRITE;
  MSC_Handle->unit[lun].state = MSC_WRITE;
  MSC_Handle->rw_lun = lun;
  USBH_MSC_SCSI_Write(phost,
                     lun,
                     address,
                     pbuf,
                     length);
  
  timeout = phost->Timer + (10000 * length);
  while (USBH_MSC_RdWrProcess(phost, lun) == USBH_BUSY)
  {
    if((phost->Timer > timeout) || (phost->device.is_connected == 0))
    {
      MSC_Handle->state = MSC_IDLE;
      return USBH_FAIL;
    }
  }
  MSC_Handle->state = MSC_IDLE;
  return USBH_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_10__ {size_t n; int /*<<< orphan*/ * Storage; } ;
struct TYPE_11__ {TYPE_3__ storids; } ;
struct TYPE_9__ {int /*<<< orphan*/  CurrentStorageId; } ;
struct TYPE_13__ {TYPE_4__ info; TYPE_2__ params; scalar_t__ is_ready; } ;
struct TYPE_8__ {TYPE_6__* pData; } ;
typedef  TYPE_6__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_MTP_SelectStorage (USBH_HandleTypeDef *phost, uint8_t storage_idx)
{
  USBH_StatusTypeDef status = USBH_FAIL;
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData;
  
  if((storage_idx < MTP_Handle->info.storids.n) && (MTP_Handle->is_ready))
  {
      MTP_Handle->params.CurrentStorageId = MTP_Handle->info.storids.Storage[storage_idx];
      status  = USBH_OK;
  }
  
  return status;
}
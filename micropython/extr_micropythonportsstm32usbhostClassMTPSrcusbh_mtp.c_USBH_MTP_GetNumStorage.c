#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_10__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  n; } ;
struct TYPE_9__ {TYPE_2__ storids; } ;
struct TYPE_11__ {scalar_t__ is_ready; TYPE_3__ info; } ;
struct TYPE_7__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_MTP_GetNumStorage (USBH_HandleTypeDef *phost, uint8_t *storage_num)
{
  USBH_StatusTypeDef status = USBH_FAIL;
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData;
  
  if(MTP_Handle->is_ready > 0)
  {
    *storage_num = MTP_Handle->info.storids.n;
    status  = USBH_OK;
  }
  
  return status;
}
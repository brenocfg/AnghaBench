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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_6__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/ * unit; } ;
struct TYPE_5__ {TYPE_3__* pData; } ;
typedef  int /*<<< orphan*/  MSC_LUNTypeDef ;
typedef  TYPE_3__ MSC_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

USBH_StatusTypeDef USBH_MSC_GetLUNInfo(USBH_HandleTypeDef *phost, uint8_t lun, MSC_LUNTypeDef *info)
{
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;    
  if(phost->gState == HOST_CLASS)
  {
    USBH_memcpy(info,&MSC_Handle->unit[lun], sizeof(MSC_LUNTypeDef));
    return USBH_OK;
  }
  else
  {
    return USBH_FAIL;
  }
}
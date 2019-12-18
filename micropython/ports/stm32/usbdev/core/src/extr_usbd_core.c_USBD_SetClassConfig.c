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
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_6__ {TYPE_1__* pClass; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_5__ {scalar_t__ (* Init ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_FAIL ; 
 int /*<<< orphan*/  USBD_OK ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

USBD_StatusTypeDef USBD_SetClassConfig(USBD_HandleTypeDef  *pdev, uint8_t cfgidx)
{
  USBD_StatusTypeDef   ret = USBD_FAIL;

  if(pdev->pClass != NULL)
  {
    /* Set configuration  and Start the Class*/
    if(pdev->pClass->Init(pdev, cfgidx) == 0)
    {
      ret = USBD_OK;
    }
  }
  return ret;
}
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
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_6__ {scalar_t__ dev_state; TYPE_1__* pClass; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/  (* SOF ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_OK ; 
 scalar_t__ USBD_STATE_CONFIGURED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

USBD_StatusTypeDef USBD_LL_SOF(USBD_HandleTypeDef  *pdev)
{
  if(pdev->dev_state == USBD_STATE_CONFIGURED)
  {
    if(pdev->pClass->SOF != NULL)
    {
      pdev->pClass->SOF(pdev);
    }
  }
  return USBD_OK;
}
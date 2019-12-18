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
struct TYPE_6__ {int /*<<< orphan*/  dev_config; TYPE_1__* pClass; int /*<<< orphan*/  dev_state; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/  (* DeInit ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_STATE_DEFAULT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

USBD_StatusTypeDef USBD_LL_DevDisconnected(USBD_HandleTypeDef  *pdev)
{
  /* Free Class Resources */
  pdev->dev_state = USBD_STATE_DEFAULT;
  pdev->pClass->DeInit(pdev, pdev->dev_config);

  return USBD_OK;
}
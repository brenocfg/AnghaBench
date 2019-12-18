#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  dev_config; TYPE_1__* pClass; int /*<<< orphan*/  dev_state; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/  (* DeInit ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_LL_DeInit (TYPE_2__*) ; 
 int /*<<< orphan*/  USBD_LL_Stop (TYPE_2__*) ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_STATE_DEFAULT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

USBD_StatusTypeDef USBD_DeInit(USBD_HandleTypeDef *pdev)
{
  /* Set Default State */
  pdev->dev_state  = USBD_STATE_DEFAULT;

  /* Free Class Resources */
  pdev->pClass->DeInit(pdev, pdev->dev_config);

    /* Stop the low level driver  */
  USBD_LL_Stop(pdev);

  /* Initialize low level driver */
  USBD_LL_DeInit(pdev);

  return USBD_OK;
}
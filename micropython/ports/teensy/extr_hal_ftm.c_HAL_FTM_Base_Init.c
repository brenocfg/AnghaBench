#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ CounterMode; int /*<<< orphan*/  PrescalerShift; int /*<<< orphan*/  Period; } ;
struct TYPE_8__ {int /*<<< orphan*/  State; TYPE_1__ Init; TYPE_2__* Instance; } ;
struct TYPE_7__ {int /*<<< orphan*/  SC; int /*<<< orphan*/  MOD; int /*<<< orphan*/  MODE; } ;
typedef  TYPE_2__ FTM_TypeDef ;
typedef  TYPE_3__ FTM_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ FTM_COUNTERMODE_CENTER ; 
 int /*<<< orphan*/  FTM_MODE_WPDIS ; 
 int /*<<< orphan*/  FTM_SC_CPWMS ; 
 int /*<<< orphan*/  FTM_SC_PS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_FTM_STATE_BUSY ; 
 int /*<<< orphan*/  HAL_FTM_STATE_READY ; 
 int /*<<< orphan*/  IS_FTM_COUNTERMODE (scalar_t__) ; 
 int /*<<< orphan*/  IS_FTM_INSTANCE (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_FTM_PERIOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_FTM_PRESCALERSHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void HAL_FTM_Base_Init(FTM_HandleTypeDef *hftm) {
    /* Check the parameters */
    FTM_TypeDef *FTMx = hftm->Instance;
    assert_param(IS_FTM_INSTANCE(FTMx));
    assert_param(IS_FTM_PRESCALERSHIFT(hftm->Init.PrescalerShift));
    assert_param(IS_FTM_COUNTERMODE(hftm->Init.CounterMode));
    assert_param(IS_FTM_PERIOD(hftm->Init.Period));

    hftm->State = HAL_FTM_STATE_BUSY;

    FTMx->MODE = FTM_MODE_WPDIS;
    FTMx->SC = 0;
    FTMx->MOD = hftm->Init.Period;
    uint32_t sc = FTM_SC_PS(hftm->Init.PrescalerShift);
    if (hftm->Init.CounterMode == FTM_COUNTERMODE_CENTER) {
      sc |= FTM_SC_CPWMS;
    }
    FTMx->SC = sc;

    hftm->State = HAL_FTM_STATE_READY;
}
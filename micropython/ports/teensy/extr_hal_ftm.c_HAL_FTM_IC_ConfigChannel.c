#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  State; TYPE_2__* Instance; } ;
struct TYPE_10__ {int /*<<< orphan*/  ICPolarity; } ;
struct TYPE_9__ {TYPE_1__* channel; } ;
struct TYPE_8__ {int /*<<< orphan*/  CSC; } ;
typedef  TYPE_2__ FTM_TypeDef ;
typedef  TYPE_3__ FTM_IC_InitTypeDef ;
typedef  TYPE_4__ FTM_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_FTM_STATE_BUSY ; 
 int /*<<< orphan*/  HAL_FTM_STATE_READY ; 
 int /*<<< orphan*/  IS_FTM_CHANNEL (size_t) ; 
 int /*<<< orphan*/  IS_FTM_IC_POLARITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_FTM_INSTANCE (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void HAL_FTM_IC_ConfigChannel(FTM_HandleTypeDef *hftm, FTM_IC_InitTypeDef* sConfig, uint32_t channel) {
    FTM_TypeDef *FTMx = hftm->Instance;
    assert_param(IS_FTM_INSTANCE(FTMx));
    assert_param(IS_FTM_CHANNEL(channel));
    assert_param(IS_FTM_IC_POLARITY(sConfig->ICPolarity));

    hftm->State = HAL_FTM_STATE_BUSY;

    FTMx->channel[channel].CSC = sConfig->ICPolarity;

    hftm->State = HAL_FTM_STATE_READY;
}
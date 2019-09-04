#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FTM_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_FTM_Base_Init (int /*<<< orphan*/ *) ; 

void HAL_FTM_PWM_Init(FTM_HandleTypeDef *hftm) {
    HAL_FTM_Base_Init(hftm);
}
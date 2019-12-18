#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Speed; int /*<<< orphan*/  Pull; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Pin; } ;
typedef  TYPE_1__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOK ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT_PP ; 
 int /*<<< orphan*/  GPIO_PIN_3 ; 
 int /*<<< orphan*/  GPIO_PIN_RESET ; 
 int /*<<< orphan*/  GPIO_PULLUP ; 
 int /*<<< orphan*/  GPIO_SPEED_FREQ_VERY_HIGH ; 
 int /*<<< orphan*/  HAL_GPIO_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HAL_GPIO_WritePin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_RCC_GPIOK_CLK_ENABLE () ; 

void STM32F7DISC_board_early_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    __HAL_RCC_GPIOK_CLK_ENABLE();

    // Turn off the backlight. LCD_BL_CTRL = PK3
    GPIO_InitStructure.Pin = GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);
}
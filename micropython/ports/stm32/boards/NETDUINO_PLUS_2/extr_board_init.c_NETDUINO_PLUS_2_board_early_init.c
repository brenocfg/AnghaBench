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
struct TYPE_3__ {void* Pin; int /*<<< orphan*/  Pull; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Speed; } ;
typedef  TYPE_1__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT_PP ; 
 void* GPIO_PIN_1 ; 
 void* GPIO_PIN_2 ; 
 int /*<<< orphan*/  GPIO_PIN_SET ; 
 int /*<<< orphan*/  GPIO_PULLUP ; 
 int /*<<< orphan*/  GPIO_SPEED_FREQ_VERY_HIGH ; 
 int /*<<< orphan*/  HAL_GPIO_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HAL_GPIO_WritePin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_RCC_GPIOB_CLK_ENABLE () ; 

void NETDUINO_PLUS_2_board_early_init(void) {

    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Turn off the backlight. LCD_BL_CTRL = PK3
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;

#if MICROPY_HW_ENABLE_SDCARD
    // Turn on the power enable for the sdcard (PB1)
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
#endif

    // Turn on the power for the 5V on the expansion header (PB2)
    GPIO_InitStructure.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}
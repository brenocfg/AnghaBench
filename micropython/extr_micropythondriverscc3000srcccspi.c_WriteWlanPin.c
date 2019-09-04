#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pin_mask; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIN_RESET ; 
 int /*<<< orphan*/  GPIO_PIN_SET ; 
 int /*<<< orphan*/  HAL_GPIO_WritePin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* PIN_EN ; 
 scalar_t__ WLAN_ENABLE ; 

void WriteWlanPin(unsigned char val)
{
    HAL_GPIO_WritePin(PIN_EN->gpio, PIN_EN->pin_mask,
            (WLAN_ENABLE)? GPIO_PIN_SET:GPIO_PIN_RESET);
}
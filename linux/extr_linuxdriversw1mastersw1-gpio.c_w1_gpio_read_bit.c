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
typedef  int u8 ;
struct w1_gpio_platform_data {int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 w1_gpio_read_bit(void *data)
{
	struct w1_gpio_platform_data *pdata = data;

	return gpiod_get_value(pdata->gpiod) ? 1 : 0;
}
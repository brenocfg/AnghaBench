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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CODEC_RESET ; 
 int /*<<< orphan*/  GPIO_MCLK_RESET ; 
 int /*<<< orphan*/  GPIO_SPDIF_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void raumfeld_enable_audio(bool en)
{
	if (en) {
		gpio_set_value(GPIO_MCLK_RESET, 1);

		/* wait some time to let the clocks become stable */
		msleep(100);

		gpio_set_value(GPIO_SPDIF_RESET, 1);
		gpio_set_value(GPIO_CODEC_RESET, 1);
	} else {
		gpio_set_value(GPIO_MCLK_RESET, 0);
		gpio_set_value(GPIO_SPDIF_RESET, 0);
		gpio_set_value(GPIO_CODEC_RESET, 0);
	}
}
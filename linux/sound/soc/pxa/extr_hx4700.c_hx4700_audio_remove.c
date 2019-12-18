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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO107_HX4700_SPK_nSD ; 
 int /*<<< orphan*/  GPIO92_HX4700_HP_DRIVER ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx4700_audio_gpios ; 

__attribute__((used)) static int hx4700_audio_remove(struct platform_device *pdev)
{
	gpio_set_value(GPIO92_HX4700_HP_DRIVER, 0);
	gpio_set_value(GPIO107_HX4700_SPK_nSD, 0);

	gpio_free_array(hx4700_audio_gpios, ARRAY_SIZE(hx4700_audio_gpios));
	return 0;
}
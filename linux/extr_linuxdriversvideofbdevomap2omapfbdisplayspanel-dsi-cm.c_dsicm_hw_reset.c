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
struct panel_drv_data {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dsicm_hw_reset(struct panel_drv_data *ddata)
{
	if (!gpio_is_valid(ddata->reset_gpio))
		return;

	gpio_set_value(ddata->reset_gpio, 1);
	udelay(10);
	/* reset the panel */
	gpio_set_value(ddata->reset_gpio, 0);
	/* assert reset */
	udelay(10);
	gpio_set_value(ddata->reset_gpio, 1);
	/* wait after releasing reset */
	usleep_range(5000, 10000);
}
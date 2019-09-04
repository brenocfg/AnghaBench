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
struct cw1200_platform_data_spi {int /*<<< orphan*/  (* clk_ctrl ) (struct cw1200_platform_data_spi const*,int) ;int /*<<< orphan*/  (* power_ctrl ) (struct cw1200_platform_data_spi const*,int) ;scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct cw1200_platform_data_spi const*,int) ; 
 int /*<<< orphan*/  stub2 (struct cw1200_platform_data_spi const*,int) ; 

__attribute__((used)) static int cw1200_spi_off(const struct cw1200_platform_data_spi *pdata)
{
	if (pdata->reset) {
		gpio_set_value(pdata->reset, 0);
		msleep(30); /* Min is 2 * CLK32K cycles */
		gpio_free(pdata->reset);
	}

	if (pdata->power_ctrl)
		pdata->power_ctrl(pdata, false);
	if (pdata->clk_ctrl)
		pdata->clk_ctrl(pdata, false);

	return 0;
}
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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_PWL_CLK_ENABLE ; 
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int /*<<< orphan*/  PWL ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osk_panel_enable(struct lcd_panel *panel)
{
	/* configure PWL pin */
	omap_cfg_reg(PWL);

	/* Enable PWL unit */
	omap_writeb(0x01, OMAP_PWL_CLK_ENABLE);

	/* Set PWL level */
	omap_writeb(0xFF, OMAP_PWL_ENABLE);

	/* set GPIO2 high (lcd power enabled) */
	gpio_set_value(2, 1);

	return 0;
}
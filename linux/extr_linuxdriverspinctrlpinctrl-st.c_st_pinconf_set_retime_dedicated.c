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
struct st_retime_dedicated {int /*<<< orphan*/ * rt; } ;
struct TYPE_2__ {struct st_retime_dedicated rt_d; } ;
struct st_pio_control {TYPE_1__ rt; } ;
struct st_pinctrl {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int RT_D_CFG_CLKNOTDATA_SHIFT ; 
 int RT_D_CFG_CLK_SHIFT ; 
 int RT_D_CFG_DELAY_INNOTOUT_SHIFT ; 
 unsigned long RT_D_CFG_DELAY_SHIFT ; 
 int RT_D_CFG_DOUBLE_EDGE_SHIFT ; 
 int RT_D_CFG_INVERTCLK_SHIFT ; 
 int RT_D_CFG_RETIME_SHIFT ; 
 scalar_t__ ST_PINCONF_UNPACK_OE (unsigned long) ; 
 int ST_PINCONF_UNPACK_RT (unsigned long) ; 
 int ST_PINCONF_UNPACK_RT_CLK (unsigned long) ; 
 int ST_PINCONF_UNPACK_RT_CLKNOTDATA (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_DELAY (unsigned long) ; 
 int ST_PINCONF_UNPACK_RT_DOUBLE_EDGE (unsigned long) ; 
 int ST_PINCONF_UNPACK_RT_INVERTCLK (unsigned long) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long st_pinconf_delay_to_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void st_pinconf_set_retime_dedicated(struct st_pinctrl *info,
	struct st_pio_control *pc, unsigned long config, int pin)
{
	int input	= ST_PINCONF_UNPACK_OE(config) ? 0 : 1;
	int clk		= ST_PINCONF_UNPACK_RT_CLK(config);
	int clknotdata	= ST_PINCONF_UNPACK_RT_CLKNOTDATA(config);
	int double_edge	= ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config);
	int invertclk	= ST_PINCONF_UNPACK_RT_INVERTCLK(config);
	int retime	= ST_PINCONF_UNPACK_RT(config);

	unsigned long delay = st_pinconf_delay_to_bit(
			ST_PINCONF_UNPACK_RT_DELAY(config),
			info->data, config);
	struct st_retime_dedicated *rt_d = &pc->rt.rt_d;

	unsigned long retime_config =
		((clk) << RT_D_CFG_CLK_SHIFT) |
		((delay) << RT_D_CFG_DELAY_SHIFT) |
		((input) << RT_D_CFG_DELAY_INNOTOUT_SHIFT) |
		((retime) << RT_D_CFG_RETIME_SHIFT) |
		((clknotdata) << RT_D_CFG_CLKNOTDATA_SHIFT) |
		((invertclk) << RT_D_CFG_INVERTCLK_SHIFT) |
		((double_edge) << RT_D_CFG_DOUBLE_EDGE_SHIFT);

	regmap_field_write(rt_d->rt[pin], retime_config);
}
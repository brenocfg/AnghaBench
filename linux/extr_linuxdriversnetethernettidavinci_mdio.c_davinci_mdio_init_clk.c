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
typedef  int u32 ;
struct TYPE_2__ {int bus_freq; } ;
struct davinci_mdio_data {int clk_div; int access_time; TYPE_1__ pdata; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int CONTROL_MAX_DIV ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int usecs_to_jiffies (int) ; 

__attribute__((used)) static void davinci_mdio_init_clk(struct davinci_mdio_data *data)
{
	u32 mdio_in, div, mdio_out_khz, access_time;

	mdio_in = clk_get_rate(data->clk);
	div = (mdio_in / data->pdata.bus_freq) - 1;
	if (div > CONTROL_MAX_DIV)
		div = CONTROL_MAX_DIV;

	data->clk_div = div;
	/*
	 * One mdio transaction consists of:
	 *	32 bits of preamble
	 *	32 bits of transferred data
	 *	24 bits of bus yield (not needed unless shared?)
	 */
	mdio_out_khz = mdio_in / (1000 * (div + 1));
	access_time  = (88 * 1000) / mdio_out_khz;

	/*
	 * In the worst case, we could be kicking off a user-access immediately
	 * after the mdio bus scan state-machine triggered its own read.  If
	 * so, our request could get deferred by one access cycle.  We
	 * defensively allow for 4 access cycles.
	 */
	data->access_time = usecs_to_jiffies(access_time * 4);
	if (!data->access_time)
		data->access_time = 1;
}
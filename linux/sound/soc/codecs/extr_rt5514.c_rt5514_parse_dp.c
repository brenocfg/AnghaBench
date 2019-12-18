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
struct TYPE_2__ {int /*<<< orphan*/  dsp_calib_clk_rate; int /*<<< orphan*/  dsp_calib_clk_name; int /*<<< orphan*/  dmic_init_delay; } ;
struct rt5514_priv {TYPE_1__ pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_property_read_string (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt5514_parse_dp(struct rt5514_priv *rt5514, struct device *dev)
{
	device_property_read_u32(dev, "realtek,dmic-init-delay-ms",
		&rt5514->pdata.dmic_init_delay);
	device_property_read_string(dev, "realtek,dsp-calib-clk-name",
		&rt5514->pdata.dsp_calib_clk_name);
	device_property_read_u32(dev, "realtek,dsp-calib-clk-rate",
		&rt5514->pdata.dsp_calib_clk_rate);

	return 0;
}
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
typedef  int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7218_dmic_clk_rate { ____Placeholder_da7218_dmic_clk_rate } da7218_dmic_clk_rate ;

/* Variables and functions */
 int DA7218_DMIC_CLK_1_5MHZ ; 
 int DA7218_DMIC_CLK_3_0MHZ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7218_dmic_clk_rate
	da7218_of_dmic_clkrate(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 1500000:
		return DA7218_DMIC_CLK_1_5MHZ;
	case 3000000:
		return DA7218_DMIC_CLK_3_0MHZ;
	default:
		dev_warn(component->dev, "Invalid DMIC clock rate");
		return DA7218_DMIC_CLK_3_0MHZ;
	}
}
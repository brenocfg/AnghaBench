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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct clk_bulk_data {char* id; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct clk_bulk_data*) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,struct clk_bulk_data*) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,struct clk_bulk_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_clk_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_bulk_data*) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 

__attribute__((used)) static int aic32x4_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	int ret;

	struct clk_bulk_data clocks[] = {
		{ .id = "madc" },
		{ .id = "mdac" },
		{ .id = "bdiv" },
	};

	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(clocks), clocks);
	if (ret)
		return ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		ret = clk_bulk_prepare_enable(ARRAY_SIZE(clocks), clocks);
		if (ret) {
			dev_err(component->dev, "Failed to enable clocks\n");
			return ret;
		}
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* Initial cold start */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			break;

		clk_bulk_disable_unprepare(ARRAY_SIZE(clocks), clocks);
		break;
	case SND_SOC_BIAS_OFF:
		break;
	}
	return 0;
}
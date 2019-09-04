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
struct tas571x_private {int /*<<< orphan*/  mclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct tas571x_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int tas571x_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	struct tas571x_private *priv = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			if (!IS_ERR(priv->mclk)) {
				ret = clk_prepare_enable(priv->mclk);
				if (ret) {
					dev_err(component->dev,
						"Failed to enable master clock: %d\n",
						ret);
					return ret;
				}
			}
		}
		break;
	case SND_SOC_BIAS_OFF:
		if (!IS_ERR(priv->mclk))
			clk_disable_unprepare(priv->mclk);
		break;
	}

	return 0;
}
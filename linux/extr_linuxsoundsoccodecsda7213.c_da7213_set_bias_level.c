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
struct da7213_priv {int /*<<< orphan*/  mclk; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int DA7213_BIAS_EN ; 
 int /*<<< orphan*/  DA7213_REFERENCES ; 
 int DA7213_VMID_EN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int da7213_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		/* Enable MCLK for transition to ON state */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY) {
			if (da7213->mclk) {
				ret = clk_prepare_enable(da7213->mclk);
				if (ret) {
					dev_err(component->dev,
						"Failed to enable mclk\n");
					return ret;
				}
			}
		}
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			/* Enable VMID reference & master bias */
			snd_soc_component_update_bits(component, DA7213_REFERENCES,
					    DA7213_VMID_EN | DA7213_BIAS_EN,
					    DA7213_VMID_EN | DA7213_BIAS_EN);
		} else {
			/* Remove MCLK */
			if (da7213->mclk)
				clk_disable_unprepare(da7213->mclk);
		}
		break;
	case SND_SOC_BIAS_OFF:
		/* Disable VMID reference & master bias */
		snd_soc_component_update_bits(component, DA7213_REFERENCES,
				    DA7213_VMID_EN | DA7213_BIAS_EN, 0);
		break;
	}
	return 0;
}
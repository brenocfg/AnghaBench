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
struct snd_soc_component {int dummy; } ;
struct ml26124_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int ML26124_BLT_ALL_ON ; 
 int ML26124_BLT_PREAMP_ON ; 
 int ML26124_MICBEN_ON ; 
 int /*<<< orphan*/  ML26124_PW_REF_PW_MNG ; 
 int /*<<< orphan*/  ML26124_PW_SPAMP_PW_MNG ; 
 int ML26124_R26_MASK ; 
 int ML26124_VMID ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct ml26124_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ml26124_set_bias_level(struct snd_soc_component *component,
		enum snd_soc_bias_level level)
{
	struct ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, ML26124_PW_SPAMP_PW_MNG,
				    ML26124_R26_MASK, ML26124_BLT_PREAMP_ON);
		msleep(100);
		snd_soc_component_update_bits(component, ML26124_PW_SPAMP_PW_MNG,
				    ML26124_R26_MASK,
				    ML26124_MICBEN_ON | ML26124_BLT_ALL_ON);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* VMID ON */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, ML26124_PW_REF_PW_MNG,
					    ML26124_VMID, ML26124_VMID);
			msleep(500);
			regcache_sync(priv->regmap);
		}
		break;
	case SND_SOC_BIAS_OFF:
		/* VMID OFF */
		snd_soc_component_update_bits(component, ML26124_PW_REF_PW_MNG,
				    ML26124_VMID, 0);
		break;
	}
	return 0;
}
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
struct tscs42xx {int /*<<< orphan*/  pll_lock; int /*<<< orphan*/  samplerate; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMSG ; 
 unsigned int RM_PLLCTL1C_PDB_PLL1 ; 
 unsigned int RM_PLLCTL1C_PDB_PLL2 ; 
 unsigned int RV_PLLCTL1C_PDB_PLL1_ENABLE ; 
 unsigned int RV_PLLCTL1C_PDB_PLL2_ENABLE ; 
 int /*<<< orphan*/  R_PLLCTL1C ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plls_locked (struct snd_soc_component*) ; 
 int sample_rate_to_pll_freq_out (int /*<<< orphan*/ ) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int power_up_audio_plls(struct snd_soc_component *component)
{
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	int freq_out;
	int ret;
	unsigned int mask;
	unsigned int val;

	freq_out = sample_rate_to_pll_freq_out(tscs42xx->samplerate);
	switch (freq_out) {
	case 122880000: /* 48k */
		mask = RM_PLLCTL1C_PDB_PLL1;
		val = RV_PLLCTL1C_PDB_PLL1_ENABLE;
		break;
	case 112896000: /* 44.1k */
		mask = RM_PLLCTL1C_PDB_PLL2;
		val = RV_PLLCTL1C_PDB_PLL2_ENABLE;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev,
				"Unrecognized PLL output freq (%d)\n", ret);
		return ret;
	}

	mutex_lock(&tscs42xx->pll_lock);

	ret = snd_soc_component_update_bits(component, R_PLLCTL1C, mask, val);
	if (ret < 0) {
		dev_err(component->dev, "Failed to turn PLL on (%d)\n", ret);
		goto exit;
	}

	if (!plls_locked(component)) {
		dev_err(component->dev, "Failed to lock plls\n");
		ret = -ENOMSG;
		goto exit;
	}

	ret = 0;
exit:
	mutex_unlock(&tscs42xx->pll_lock);

	return ret;
}
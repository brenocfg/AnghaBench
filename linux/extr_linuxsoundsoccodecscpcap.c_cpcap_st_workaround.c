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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct cpcap_audio {scalar_t__ vendor; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_REG_ST_TEST1 ; 
 int /*<<< orphan*/  CPCAP_REG_TEST ; 
 scalar_t__ CPCAP_VENDOR_ST ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  STM_STDAC_ACTIVATE_RAMP_TIME ; 
 int /*<<< orphan*/  STM_STDAC_EN_ST_TEST1_POST ; 
 int /*<<< orphan*/  STM_STDAC_EN_ST_TEST1_PRE ; 
 int /*<<< orphan*/  STM_STDAC_EN_TEST_POST ; 
 int /*<<< orphan*/  STM_STDAC_EN_TEST_PRE ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpcap_audio* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_st_workaround(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	int err = 0;

	/* Only CPCAP from ST requires workaround */
	if (cpcap->vendor != CPCAP_VENDOR_ST)
		return 0;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		err = regmap_write(cpcap->regmap, CPCAP_REG_TEST,
				   STM_STDAC_EN_TEST_PRE);
		if (err)
			return err;
		err = regmap_write(cpcap->regmap, CPCAP_REG_ST_TEST1,
				   STM_STDAC_EN_ST_TEST1_PRE);
		break;
	case SND_SOC_DAPM_POST_PMU:
		msleep(STM_STDAC_ACTIVATE_RAMP_TIME);

		err = regmap_write(cpcap->regmap, CPCAP_REG_ST_TEST1,
				   STM_STDAC_EN_ST_TEST1_POST);
		if (err)
			return err;
		err = regmap_write(cpcap->regmap, CPCAP_REG_TEST,
				   STM_STDAC_EN_TEST_POST);
		break;
	default:
		break;
	}

	return err;
}
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
struct sti_sas_data {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIF_BIPHASE_ENABLE_MASK ; 
 int /*<<< orphan*/  SPDIF_BIPHASE_IDLE_MASK ; 
 int /*<<< orphan*/  STIH407_AUDIO_DAC_CTRL ; 
 int /*<<< orphan*/  STIH407_AUDIO_GLUE_CTRL ; 
 int /*<<< orphan*/  STIH407_DAC_SOFTMUTE_MASK ; 
 int /*<<< orphan*/  STIH407_DAC_STANDBY_ANA_MASK ; 
 int /*<<< orphan*/  STIH407_DAC_STANDBY_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  sti_sas_init_sas_registers(struct snd_soc_component *component,
				       struct sti_sas_data *data)
{
	int ret;
	/*
	 * DAC and SPDIF are activated by default
	 * put them in IDLE to save power
	 */

	/* Initialise bi-phase formatter to disabled */
	ret = snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
				  SPDIF_BIPHASE_ENABLE_MASK, 0);

	if (!ret)
		/* Initialise bi-phase formatter idle value to 0 */
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_GLUE_CTRL,
					  SPDIF_BIPHASE_IDLE_MASK, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to update SPDIF registers\n");
		return ret;
	}

	/* Init DAC configuration */
	/* init configuration */
	ret =  snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
				   STIH407_DAC_STANDBY_MASK,
				   STIH407_DAC_STANDBY_MASK);

	if (!ret)
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					  STIH407_DAC_STANDBY_ANA_MASK,
					  STIH407_DAC_STANDBY_ANA_MASK);
	if (!ret)
		ret = snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					  STIH407_DAC_SOFTMUTE_MASK,
					  STIH407_DAC_SOFTMUTE_MASK);

	if (ret < 0) {
		dev_err(component->dev, "Failed to update DAC registers\n");
		return ret;
	}

	return ret;
}
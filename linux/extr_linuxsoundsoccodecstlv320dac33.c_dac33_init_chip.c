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
struct tlv320dac33_priv {int /*<<< orphan*/  chip_power; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC33_ANA_VOL_SOFT_STEP_CTRL ; 
 int DAC33_DACRATE (int /*<<< orphan*/ ) ; 
 int DAC33_DACSRCL_LEFT ; 
 int DAC33_DACSRCR_RIGHT ; 
 int /*<<< orphan*/  DAC33_DAC_CTRL_A ; 
 int /*<<< orphan*/  DAC33_DAC_CTRL_B ; 
 int /*<<< orphan*/  DAC33_DAC_CTRL_C ; 
 int /*<<< orphan*/  DAC33_LDAC_DIG_VOL_CTRL ; 
 int /*<<< orphan*/  DAC33_LDAC_PWR_CTRL ; 
 int /*<<< orphan*/  DAC33_LINEL_TO_LLO_VOL ; 
 int /*<<< orphan*/  DAC33_LINER_TO_RLO_VOL ; 
 int /*<<< orphan*/  DAC33_OUT_AMP_CTRL ; 
 int /*<<< orphan*/  DAC33_RDAC_DIG_VOL_CTRL ; 
 int /*<<< orphan*/  DAC33_RDAC_PWR_CTRL ; 
 int DAC33_VOLCLKEN ; 
 int dac33_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dac33_init_chip(struct snd_soc_component *component)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	if (unlikely(!dac33->chip_power))
		return;

	/* A : DAC sample rate Fsref/1.5 */
	dac33_write(component, DAC33_DAC_CTRL_A, DAC33_DACRATE(0));
	/* B : DAC src=normal, not muted */
	dac33_write(component, DAC33_DAC_CTRL_B, DAC33_DACSRCR_RIGHT |
					     DAC33_DACSRCL_LEFT);
	/* C : (defaults) */
	dac33_write(component, DAC33_DAC_CTRL_C, 0x00);

	/* 73 : volume soft stepping control,
	 clock source = internal osc (?) */
	dac33_write(component, DAC33_ANA_VOL_SOFT_STEP_CTRL, DAC33_VOLCLKEN);

	/* Restore only selected registers (gains mostly) */
	dac33_write(component, DAC33_LDAC_DIG_VOL_CTRL,
		    dac33_read_reg_cache(component, DAC33_LDAC_DIG_VOL_CTRL));
	dac33_write(component, DAC33_RDAC_DIG_VOL_CTRL,
		    dac33_read_reg_cache(component, DAC33_RDAC_DIG_VOL_CTRL));

	dac33_write(component, DAC33_LINEL_TO_LLO_VOL,
		    dac33_read_reg_cache(component, DAC33_LINEL_TO_LLO_VOL));
	dac33_write(component, DAC33_LINER_TO_RLO_VOL,
		    dac33_read_reg_cache(component, DAC33_LINER_TO_RLO_VOL));

	dac33_write(component, DAC33_OUT_AMP_CTRL,
		    dac33_read_reg_cache(component, DAC33_OUT_AMP_CTRL));

	dac33_write(component, DAC33_LDAC_PWR_CTRL,
		    dac33_read_reg_cache(component, DAC33_LDAC_PWR_CTRL));
	dac33_write(component, DAC33_RDAC_PWR_CTRL,
		    dac33_read_reg_cache(component, DAC33_RDAC_PWR_CTRL));
}
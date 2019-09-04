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
struct snd_cs46xx {int /*<<< orphan*/  spos_mutex; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int adc_input; int /*<<< orphan*/  codec_in_scb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCMSERIALIN_SCB_ADDR ; 
 int cs46xx_add_record_source (struct snd_cs46xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int cs46xx_dsp_enable_adc_capture (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(ins->adc_input))
		return -EINVAL;
	if (snd_BUG_ON(!ins->codec_in_scb))
		return -EINVAL;

	mutex_lock(&chip->spos_mutex);
	ins->adc_input = cs46xx_add_record_source(chip,ins->codec_in_scb,PCMSERIALIN_SCB_ADDR,
						  "PCMSerialInput_ADC");
	mutex_unlock(&chip->spos_mutex);

	return 0;
}
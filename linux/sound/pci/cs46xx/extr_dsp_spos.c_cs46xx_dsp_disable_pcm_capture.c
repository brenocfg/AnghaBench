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
struct dsp_spos_instance {int /*<<< orphan*/ * pcm_input; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cs46xx_dsp_remove_scb (struct snd_cs46xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int cs46xx_dsp_disable_pcm_capture (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins->pcm_input))
		return -EINVAL;

	mutex_lock(&chip->spos_mutex);
	cs46xx_dsp_remove_scb (chip,ins->pcm_input);
	ins->pcm_input = NULL;
	mutex_unlock(&chip->spos_mutex);

	return 0;
}
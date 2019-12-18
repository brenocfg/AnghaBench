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
struct snd_cs46xx {int /*<<< orphan*/  (* amplifier_ctrl ) (struct snd_cs46xx*,int) ;int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;int /*<<< orphan*/  spos_mutex; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {scalar_t__ spdif_status_in; int /*<<< orphan*/  spdif_in_src; int /*<<< orphan*/ * asynch_rx_scb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cs46xx_dsp_remove_scb (struct snd_cs46xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs46xx_src_unlink (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_cs46xx*,int) ; 

int cs46xx_dsp_disable_spdif_in (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins->asynch_rx_scb))
		return -EINVAL;
	if (snd_BUG_ON(!ins->spdif_in_src))
		return -EINVAL;

	mutex_lock(&chip->spos_mutex);

	/* Remove the asynchronous receiver SCB */
	cs46xx_dsp_remove_scb (chip,ins->asynch_rx_scb);
	ins->asynch_rx_scb = NULL;

	cs46xx_src_unlink(chip,ins->spdif_in_src);

	/* monitor state */
	ins->spdif_status_in = 0;
	mutex_unlock(&chip->spos_mutex);

	/* restore amplifier */
	chip->active_ctrl(chip, -1);
	chip->amplifier_ctrl(chip, -1);

	return 0;
}
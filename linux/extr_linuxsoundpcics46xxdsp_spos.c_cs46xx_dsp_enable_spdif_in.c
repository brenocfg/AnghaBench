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
struct snd_cs46xx {int /*<<< orphan*/  spos_mutex; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  (* amplifier_ctrl ) (struct snd_cs46xx*,int) ;int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int asynch_rx_scb; int spdif_status_out; int spdif_status_in; int /*<<< orphan*/  spdif_in_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCRX_SCB_ADDR ; 
 int DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED ; 
 int EINVAL ; 
 int /*<<< orphan*/  SCB_ON_PARENT_SUBLIST_SCB ; 
 int /*<<< orphan*/  SPDIFI_IP_OUTPUT_BUFFER1 ; 
 int /*<<< orphan*/  SPDIFI_SCB_INST ; 
 int /*<<< orphan*/  SP_ASER_COUNTDOWN ; 
 int /*<<< orphan*/  SP_SPDIN_CONTROL ; 
 int cs46xx_dsp_create_asynch_fg_rx_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs46xx_dsp_scb_set_volume (struct snd_cs46xx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cs46xx_poke_via_dsp (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cs46xx_src_link (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_cs46xx*,int) ; 

int cs46xx_dsp_enable_spdif_in (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* turn on amplifier */
	chip->active_ctrl(chip, 1);
	chip->amplifier_ctrl(chip, 1);

	if (snd_BUG_ON(ins->asynch_rx_scb))
		return -EINVAL;
	if (snd_BUG_ON(!ins->spdif_in_src))
		return -EINVAL;

	mutex_lock(&chip->spos_mutex);

	if ( ! (ins->spdif_status_out & DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED) ) {
		/* time countdown enable */
		cs46xx_poke_via_dsp (chip,SP_ASER_COUNTDOWN, 0x80000005);
		/* NOTE: 80000005 value is just magic. With all values
		   that I've tested this one seem to give the best result.
		   Got no explication why. (Benny) */

		/* SPDIF input MASTER ENABLE */
		cs46xx_poke_via_dsp (chip,SP_SPDIN_CONTROL, 0x800003ff);

		ins->spdif_status_out |= DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED;
	}

	/* create and start the asynchronous receiver SCB */
	ins->asynch_rx_scb = cs46xx_dsp_create_asynch_fg_rx_scb(chip,"AsynchFGRxSCB",
								ASYNCRX_SCB_ADDR,
								SPDIFI_SCB_INST,
								SPDIFI_IP_OUTPUT_BUFFER1,
								ins->spdif_in_src,
								SCB_ON_PARENT_SUBLIST_SCB);

	spin_lock_irq(&chip->reg_lock);

	/* reset SPDIF input sample buffer pointer */
	/*snd_cs46xx_poke (chip, (SPDIFI_SCB_INST + 0x0c) << 2,
	  (SPDIFI_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC);*/

	/* reset FIFO ptr */
	/*cs46xx_poke_via_dsp (chip,SP_SPDIN_FIFOPTR, 0x0);*/
	cs46xx_src_link(chip,ins->spdif_in_src);

	/* unmute SRC volume */
	cs46xx_dsp_scb_set_volume (chip,ins->spdif_in_src,0x7fff,0x7fff);

	spin_unlock_irq(&chip->reg_lock);

	/* set SPDIF input sample rate and unmute
	   NOTE: only 48khz support for SPDIF input this time */
	/* cs46xx_dsp_set_src_sample_rate(chip,ins->spdif_in_src,48000); */

	/* monitor state */
	ins->spdif_status_in = 1;
	mutex_unlock(&chip->spos_mutex);

	return 0;
}
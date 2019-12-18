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
typedef  void* u16 ;
struct snd_cs46xx {int /*<<< orphan*/  spos_mutex; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {void* spdif_input_volume_right; void* spdif_input_volume_left; int /*<<< orphan*/ * asynch_rx_scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs46xx_dsp_scb_set_volume (struct snd_cs46xx*,int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cs46xx_dsp_set_iec958_volume (struct snd_cs46xx * chip, u16 left, u16 right)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	mutex_lock(&chip->spos_mutex);

	if (ins->asynch_rx_scb != NULL)
		cs46xx_dsp_scb_set_volume (chip,ins->asynch_rx_scb,
					   left,right);

	ins->spdif_input_volume_left = left;
	ins->spdif_input_volume_right = right;

	mutex_unlock(&chip->spos_mutex);

	return 0;
}
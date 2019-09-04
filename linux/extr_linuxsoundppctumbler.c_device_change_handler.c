#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct snd_pmac {TYPE_1__* hp_detect_ctl; int /*<<< orphan*/  card; int /*<<< orphan*/  lineout_sw_ctl; int /*<<< orphan*/  master_sw_ctl; int /*<<< orphan*/  speaker_sw_ctl; struct pmac_tumbler* mixer_data; } ;
struct TYPE_4__ {scalar_t__ addr; } ;
struct pmac_tumbler {scalar_t__ auto_mute_notify; TYPE_2__ line_mute; TYPE_2__ hp_mute; scalar_t__ anded_reset; TYPE_2__ amp_mute; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  IS_G4DA ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  check_mute (struct snd_pmac*,TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct snd_pmac* device_change_chip ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tumbler_detect_headphone (struct snd_pmac*) ; 
 int tumbler_detect_lineout (struct snd_pmac*) ; 
 int /*<<< orphan*/  tumbler_set_master_volume (struct pmac_tumbler*) ; 

__attribute__((used)) static void device_change_handler(struct work_struct *work)
{
	struct snd_pmac *chip = device_change_chip;
	struct pmac_tumbler *mix;
	int headphone, lineout;

	if (!chip)
		return;

	mix = chip->mixer_data;
	if (snd_BUG_ON(!mix))
		return;

	headphone = tumbler_detect_headphone(chip);
	lineout = tumbler_detect_lineout(chip);

	DBG("headphone: %d, lineout: %d\n", headphone, lineout);

	if (headphone || lineout) {
		/* unmute headphone/lineout & mute speaker */
		if (headphone)
			check_mute(chip, &mix->hp_mute, 0, mix->auto_mute_notify,
				   chip->master_sw_ctl);
		if (lineout && mix->line_mute.addr != 0)
			check_mute(chip, &mix->line_mute, 0, mix->auto_mute_notify,
				   chip->lineout_sw_ctl);
		if (mix->anded_reset)
			msleep(10);
		check_mute(chip, &mix->amp_mute, !IS_G4DA, mix->auto_mute_notify,
			   chip->speaker_sw_ctl);
	} else {
		/* unmute speaker, mute others */
		check_mute(chip, &mix->amp_mute, 0, mix->auto_mute_notify,
			   chip->speaker_sw_ctl);
		if (mix->anded_reset)
			msleep(10);
		check_mute(chip, &mix->hp_mute, 1, mix->auto_mute_notify,
			   chip->master_sw_ctl);
		if (mix->line_mute.addr != 0)
			check_mute(chip, &mix->line_mute, 1, mix->auto_mute_notify,
				   chip->lineout_sw_ctl);
	}
	if (mix->auto_mute_notify)
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->hp_detect_ctl->id);

#ifdef CONFIG_SND_POWERMAC_AUTO_DRC
	mix->drc_enable = ! (headphone || lineout);
	if (mix->auto_mute_notify)
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->drc_sw_ctl->id);
	if (chip->model == PMAC_TUMBLER)
		tumbler_set_drc(mix);
	else
		snapper_set_drc(mix);
#endif

	/* reset the master volume so the correct amplification is applied */
	tumbler_set_master_volume(mix);
}
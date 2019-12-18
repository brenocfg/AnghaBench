#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pmac {int* awacs_reg; TYPE_3__* hp_detect_ctl; int /*<<< orphan*/  card; TYPE_2__* speaker_sw_ctl; TYPE_1__* master_sw_ctl; struct awacs_amp* mixer_data; scalar_t__ auto_mute; } ;
struct awacs_amp {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMP_CH_HD ; 
 int /*<<< orphan*/  AMP_CH_SPK ; 
 int MASK_HDMUTE ; 
 int MASK_PAROUT1 ; 
 int MASK_SPKMUTE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 scalar_t__ imac1 ; 
 scalar_t__ imac2 ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pmac_awacs_detect_headphone (struct snd_pmac*) ; 
 int /*<<< orphan*/  snd_pmac_awacs_write_reg (struct snd_pmac*,int,int) ; 
 int toggle_amp_mute (struct awacs_amp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_pmac_awacs_update_automute(struct snd_pmac *chip, int do_notify)
{
	if (chip->auto_mute) {
#ifdef PMAC_AMP_AVAIL
		if (chip->mixer_data) {
			struct awacs_amp *amp = chip->mixer_data;
			int changed;
			if (snd_pmac_awacs_detect_headphone(chip)) {
				changed = toggle_amp_mute(amp, AMP_CH_HD, 0);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 1);
			} else {
				changed = toggle_amp_mute(amp, AMP_CH_HD, 1);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 0);
			}
			if (do_notify && ! changed)
				return;
		} else
#endif
		{
			int reg = chip->awacs_reg[1]
				| (MASK_HDMUTE | MASK_SPKMUTE);
			if (imac1) {
				reg &= ~MASK_SPKMUTE;
				reg |= MASK_PAROUT1;
			} else if (imac2) {
				reg &= ~MASK_SPKMUTE;
				reg &= ~MASK_PAROUT1;
			}
			if (snd_pmac_awacs_detect_headphone(chip))
				reg &= ~MASK_HDMUTE;
			else if (imac1)
				reg &= ~MASK_PAROUT1;
			else if (imac2)
				reg |= MASK_PAROUT1;
			else
				reg &= ~MASK_SPKMUTE;
			if (do_notify && reg == chip->awacs_reg[1])
				return;
			snd_pmac_awacs_write_reg(chip, 1, reg);
		}
		if (do_notify) {
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_sw_ctl->id);
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->speaker_sw_ctl->id);
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->hp_detect_ctl->id);
		}
	}
}
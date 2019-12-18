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
struct snd_pmac {TYPE_3__* hp_detect_ctl; int /*<<< orphan*/  card; TYPE_2__* speaker_sw_ctl; TYPE_1__* master_sw_ctl; scalar_t__ auto_mute; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BURGUNDY_HP_LEFT ; 
 int BURGUNDY_HP_RIGHT ; 
 int BURGUNDY_OUTPUT_INTERN ; 
 int BURGUNDY_OUTPUT_LEFT ; 
 int BURGUNDY_OUTPUT_RIGHT ; 
 int /*<<< orphan*/  MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pmac_burgundy_detect_headphone (struct snd_pmac*) ; 
 int snd_pmac_burgundy_rcb (struct snd_pmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pmac_burgundy_wcb (struct snd_pmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_pmac_burgundy_update_automute(struct snd_pmac *chip, int do_notify)
{
	if (chip->auto_mute) {
		int imac = of_machine_is_compatible("iMac");
		int reg, oreg;
		reg = oreg = snd_pmac_burgundy_rcb(chip,
				MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES);
		reg &= imac ? ~(BURGUNDY_OUTPUT_LEFT | BURGUNDY_OUTPUT_RIGHT
				| BURGUNDY_HP_LEFT | BURGUNDY_HP_RIGHT)
			: ~(BURGUNDY_OUTPUT_LEFT | BURGUNDY_OUTPUT_RIGHT
				| BURGUNDY_OUTPUT_INTERN);
		if (snd_pmac_burgundy_detect_headphone(chip))
			reg |= imac ? (BURGUNDY_HP_LEFT | BURGUNDY_HP_RIGHT)
				: (BURGUNDY_OUTPUT_LEFT
					| BURGUNDY_OUTPUT_RIGHT);
		else
			reg |= imac ? (BURGUNDY_OUTPUT_LEFT
					| BURGUNDY_OUTPUT_RIGHT)
				: (BURGUNDY_OUTPUT_INTERN);
		if (do_notify && reg == oreg)
			return;
		snd_pmac_burgundy_wcb(chip,
				MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES, reg);
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
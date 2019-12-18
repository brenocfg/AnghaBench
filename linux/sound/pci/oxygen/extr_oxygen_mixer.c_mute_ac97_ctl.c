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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* ac97_switch ) (struct oxygen*,unsigned int,int) ;} ;
struct oxygen {TYPE_2__** controls; int /*<<< orphan*/  card; TYPE_1__ model; } ;
struct TYPE_4__ {int private_value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int oxygen_read_ac97 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  oxygen_write_ac97 (struct oxygen*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*,unsigned int,int) ; 

__attribute__((used)) static void mute_ac97_ctl(struct oxygen *chip, unsigned int control)
{
	unsigned int priv_idx;
	u16 value;

	if (!chip->controls[control])
		return;
	priv_idx = chip->controls[control]->private_value & 0xff;
	value = oxygen_read_ac97(chip, 0, priv_idx);
	if (!(value & 0x8000)) {
		oxygen_write_ac97(chip, 0, priv_idx, value | 0x8000);
		if (chip->model.ac97_switch)
			chip->model.ac97_switch(chip, priv_idx, 0x8000);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->controls[control]->id);
	}
}
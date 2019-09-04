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
struct snd_wss {int* image; int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 size_t CS4231_ALT_FEATURE_1 ; 
 struct snd_wss* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_cs4236_get_iec958_switch(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wss *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.integer.value[0] = chip->image[CS4231_ALT_FEATURE_1] & 0x02 ? 1 : 0;
#if 0
	printk(KERN_DEBUG "get valid: ALT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_ALT_FEATURE_1),
			snd_cs4236_ctrl_in(chip, 3),
			snd_cs4236_ctrl_in(chip, 4),
			snd_cs4236_ctrl_in(chip, 5),
			snd_cs4236_ctrl_in(chip, 6),
			snd_cs4236_ctrl_in(chip, 8));
#endif
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}
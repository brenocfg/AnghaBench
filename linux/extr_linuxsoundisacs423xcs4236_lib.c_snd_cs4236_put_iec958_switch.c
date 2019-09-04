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
struct snd_wss {int* image; int /*<<< orphan*/  mce_mutex; int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 size_t CS4231_ALT_FEATURE_1 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_cs4236_ctrl_in (struct snd_wss*,int) ; 
 int /*<<< orphan*/  snd_cs4236_ctrl_out (struct snd_wss*,int,unsigned short) ; 
 struct snd_wss* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_wss_mce_down (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_mce_up (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_cs4236_put_iec958_switch(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wss *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int change;
	unsigned short enable, val;
	
	enable = ucontrol->value.integer.value[0] & 1;

	mutex_lock(&chip->mce_mutex);
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	val = (chip->image[CS4231_ALT_FEATURE_1] & ~0x0e) | (0<<2) | (enable << 1);
	change = val != chip->image[CS4231_ALT_FEATURE_1];
	snd_wss_out(chip, CS4231_ALT_FEATURE_1, val);
	val = snd_cs4236_ctrl_in(chip, 4) | 0xc0;
	snd_cs4236_ctrl_out(chip, 4, val);
	udelay(100);
	val &= ~0x40;
	snd_cs4236_ctrl_out(chip, 4, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_down(chip);
	mutex_unlock(&chip->mce_mutex);

#if 0
	printk(KERN_DEBUG "set valid: ALT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_ALT_FEATURE_1),
			snd_cs4236_ctrl_in(chip, 3),
			snd_cs4236_ctrl_in(chip, 4),
			snd_cs4236_ctrl_in(chip, 5),
			snd_cs4236_ctrl_in(chip, 6),
			snd_cs4236_ctrl_in(chip, 8));
#endif
	return change;
}
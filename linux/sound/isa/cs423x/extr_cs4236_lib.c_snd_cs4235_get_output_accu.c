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
struct snd_wss {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * image; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {void** value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 size_t CS4235_LEFT_MASTER ; 
 size_t CS4235_RIGHT_MASTER ; 
 void* snd_cs4235_mixer_output_accu_get_volume (int /*<<< orphan*/ ) ; 
 struct snd_wss* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_cs4235_get_output_accu(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wss *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.integer.value[0] = snd_cs4235_mixer_output_accu_get_volume(chip->image[CS4235_LEFT_MASTER]);
	ucontrol->value.integer.value[1] = snd_cs4235_mixer_output_accu_get_volume(chip->image[CS4235_RIGHT_MASTER]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}
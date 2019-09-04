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
struct sonicvibes {int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_IREG_LEFT_ADC ; 
 int /*<<< orphan*/  SV_IREG_RIGHT_ADC ; 
 int SV_RECSRC_OUT ; 
 struct sonicvibes* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_sonicvibes_in1 (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sonicvibes_get_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&sonic->reg_lock);
	ucontrol->value.enumerated.item[0] = ((snd_sonicvibes_in1(sonic, SV_IREG_LEFT_ADC) & SV_RECSRC_OUT) >> 5) - 1;
	ucontrol->value.enumerated.item[1] = ((snd_sonicvibes_in1(sonic, SV_IREG_RIGHT_ADC) & SV_RECSRC_OUT) >> 5) - 1;
	spin_unlock_irq(&sonic->reg_lock);
	return 0;
}
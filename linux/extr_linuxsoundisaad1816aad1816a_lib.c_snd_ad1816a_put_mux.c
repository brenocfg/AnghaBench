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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ad1816a {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_ADC_SOURCE_SEL ; 
 int EINVAL ; 
 unsigned short snd_ad1816a_read (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ad1816a_write (struct snd_ad1816a*,int /*<<< orphan*/ ,unsigned short) ; 
 struct snd_ad1816a* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ad1816a_put_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	unsigned short val;
	int change;
	
	if (ucontrol->value.enumerated.item[0] > 6 ||
	    ucontrol->value.enumerated.item[1] > 6)
		return -EINVAL;
	val = (ucontrol->value.enumerated.item[0] << 12) |
	      (ucontrol->value.enumerated.item[1] << 4);
	spin_lock_irqsave(&chip->lock, flags);
	change = snd_ad1816a_read(chip, AD1816A_ADC_SOURCE_SEL) != val;
	snd_ad1816a_write(chip, AD1816A_ADC_SOURCE_SEL, val);
	spin_unlock_irqrestore(&chip->lock, flags);
	return change;
}
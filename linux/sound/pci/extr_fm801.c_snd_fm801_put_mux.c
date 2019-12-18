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
struct TYPE_3__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fm801 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM801_REC_SRC ; 
 int snd_fm801_update_bits (struct fm801*,int /*<<< orphan*/ ,int,unsigned short) ; 
 struct fm801* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_fm801_put_mux(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct fm801 *chip = snd_kcontrol_chip(kcontrol);
        unsigned short val;
 
        if ((val = ucontrol->value.enumerated.item[0]) > 4)
                return -EINVAL;
	return snd_fm801_update_bits(chip, FM801_REC_SRC, 7, val);
}
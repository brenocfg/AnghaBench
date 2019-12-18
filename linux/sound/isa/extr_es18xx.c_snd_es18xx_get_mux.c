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
struct snd_es18xx {int version; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int snd_es18xx_mixer_read (struct snd_es18xx*,int) ; 
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_es18xx_get_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	static unsigned char invMap4Source[8] = {0, 0, 1, 1, 0, 0, 2, 3};
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	int muxSource = snd_es18xx_mixer_read(chip, 0x1c) & 0x07;
	if (!(chip->version == 0x1869 || chip->version == 0x1879)) {
		muxSource = invMap4Source[muxSource];
		if (muxSource==3 && 
		    (chip->version == 0x1887 || chip->version == 0x1888) &&
		    (snd_es18xx_mixer_read(chip, 0x7a) & 0x08)
		) 
			muxSource = 4;
	}
	ucontrol->value.enumerated.item[0] = muxSource;
	return 0;
}
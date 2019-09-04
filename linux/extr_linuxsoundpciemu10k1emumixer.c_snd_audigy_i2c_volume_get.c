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
struct snd_kcontrol {unsigned int private_value; } ;
struct snd_emu10k1 {int /*<<< orphan*/ ** i2c_capture_volume; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_audigy_i2c_volume_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int source_id;

	source_id = kcontrol->private_value;
	/* Limit: emu->i2c_capture_volume */
        /*        capture_source: uinfo->value.enumerated.items = 2 */
	if (source_id >= 2)
		return -EINVAL;

	ucontrol->value.integer.value[0] = emu->i2c_capture_volume[source_id][0];
	ucontrol->value.integer.value[1] = emu->i2c_capture_volume[source_id][1];
	return 0;
}
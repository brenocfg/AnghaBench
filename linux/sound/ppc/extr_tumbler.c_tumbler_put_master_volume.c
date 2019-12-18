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
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pmac_tumbler {unsigned int* master_vol; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  master_volume_table ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  tumbler_set_master_volume (struct pmac_tumbler*) ; 

__attribute__((used)) static int tumbler_put_master_volume(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	struct pmac_tumbler *mix = chip->mixer_data;
	unsigned int vol[2];
	int change;

	vol[0] = ucontrol->value.integer.value[0];
	vol[1] = ucontrol->value.integer.value[1];
	if (vol[0] >= ARRAY_SIZE(master_volume_table) ||
	    vol[1] >= ARRAY_SIZE(master_volume_table))
		return -EINVAL;
	change = mix->master_vol[0] != vol[0] ||
		mix->master_vol[1] != vol[1];
	if (change) {
		mix->master_vol[0] = vol[0];
		mix->master_vol[1] = vol[1];
		tumbler_set_master_volume(mix);
	}
	return change;
}
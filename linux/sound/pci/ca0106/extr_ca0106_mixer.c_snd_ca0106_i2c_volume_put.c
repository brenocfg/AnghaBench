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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ca0106 {unsigned int** i2c_capture_volume; int i2c_capture_source; } ;
typedef  int /*<<< orphan*/  ngain ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_ATTEN_ADCL ; 
 int /*<<< orphan*/  ADC_ATTEN_ADCR ; 
 int EINVAL ; 
 int /*<<< orphan*/  snd_ca0106_i2c_write (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ca0106* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ca0106_i2c_volume_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
        struct snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
        unsigned int ogain;
        unsigned int ngain;
	int source_id;
	int change = 0;

	source_id = kcontrol->private_value;
	ogain = emu->i2c_capture_volume[source_id][0]; /* Left */
	ngain = ucontrol->value.integer.value[0];
	if (ngain > 0xff)
		return -EINVAL;
	if (ogain != ngain) {
		if (emu->i2c_capture_source == source_id)
			snd_ca0106_i2c_write(emu, ADC_ATTEN_ADCL, ((ngain) & 0xff) );
		emu->i2c_capture_volume[source_id][0] = ucontrol->value.integer.value[0];
		change = 1;
	}
	ogain = emu->i2c_capture_volume[source_id][1]; /* Right */
	ngain = ucontrol->value.integer.value[1];
	if (ngain > 0xff)
		return -EINVAL;
	if (ogain != ngain) {
		if (emu->i2c_capture_source == source_id)
			snd_ca0106_i2c_write(emu, ADC_ATTEN_ADCR, ((ngain) & 0xff));
		emu->i2c_capture_volume[source_id][1] = ucontrol->value.integer.value[1];
		change = 1;
	}

	return change;
}
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
struct snd_usb_caiaqdev {int* control_state; } ;
struct snd_usb_audio {int /*<<< orphan*/  card; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int CNT_INTVAL ; 
 struct snd_usb_caiaqdev* caiaqdev (int /*<<< orphan*/ ) ; 
 struct snd_usb_audio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int control_get(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	struct snd_usb_caiaqdev *cdev = caiaqdev(chip->card);
	int pos = kcontrol->private_value;

	if (pos & CNT_INTVAL)
		ucontrol->value.integer.value[0]
			= cdev->control_state[pos & ~CNT_INTVAL];
	else
		ucontrol->value.integer.value[0]
			= !!(cdev->control_state[pos / 8] & (1 << pos % 8));

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_7__ {int* value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct control_runtime {unsigned int output_mute; TYPE_2__* chip; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct control_runtime* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int usb6fire_control_output_mute_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct control_runtime *rt = snd_kcontrol_chip(kcontrol);
	unsigned int ch = kcontrol->private_value;
	u8 value = rt->output_mute >> ch;

	if (ch > 4) {
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		return -EINVAL;
	}

	ucontrol->value.integer.value[0] = 1 & value;
	value >>= 1;
	ucontrol->value.integer.value[1] = 1 & value;

	return 0;
}
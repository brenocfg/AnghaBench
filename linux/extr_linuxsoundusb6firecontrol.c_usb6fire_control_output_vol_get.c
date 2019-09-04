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
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct control_runtime {int /*<<< orphan*/ * output_vol; TYPE_3__* chip; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct control_runtime* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int usb6fire_control_output_vol_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct control_runtime *rt = snd_kcontrol_chip(kcontrol);
	unsigned int ch = kcontrol->private_value;

	if (ch > 4) {
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		return -EINVAL;
	}

	ucontrol->value.integer.value[0] = rt->output_vol[ch];
	ucontrol->value.integer.value[1] = rt->output_vol[ch + 1];
	return 0;
}
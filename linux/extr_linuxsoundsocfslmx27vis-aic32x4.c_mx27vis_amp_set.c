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
struct soc_mixer_control {unsigned int reg; int max; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MX27VIS_AMP_GAIN 129 
#define  MX27VIS_AMP_MUTE 128 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int mx27vis_amp_gain ; 
 int /*<<< orphan*/  mx27vis_amp_gain0_gpio ; 
 int /*<<< orphan*/  mx27vis_amp_gain1_gpio ; 
 int mx27vis_amp_mute ; 
 int /*<<< orphan*/  mx27vis_amp_mutel_gpio ; 
 int /*<<< orphan*/  mx27vis_amp_muter_gpio ; 

__attribute__((used)) static int mx27vis_amp_set(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int value = ucontrol->value.integer.value[0];
	unsigned int reg = mc->reg;
	int max = mc->max;

	if (value > max)
		return -EINVAL;

	switch (reg) {
	case MX27VIS_AMP_GAIN:
		gpio_set_value(mx27vis_amp_gain0_gpio, value & 1);
		gpio_set_value(mx27vis_amp_gain1_gpio, value >> 1);
		mx27vis_amp_gain = value;
		break;
	case MX27VIS_AMP_MUTE:
		gpio_set_value(mx27vis_amp_mutel_gpio, value & 1);
		gpio_set_value(mx27vis_amp_muter_gpio, value >> 1);
		mx27vis_amp_mute = value;
		break;
	}
	return 0;
}
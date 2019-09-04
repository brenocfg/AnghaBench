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
typedef  int u32 ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_hal2 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H2I_ADC_C2 ; 
 int H2I_C2_L_ATT_SHIFT ; 
 int H2I_C2_L_GAIN_SHIFT ; 
 int H2I_C2_MUTE ; 
 int H2I_C2_R_ATT_SHIFT ; 
 int H2I_C2_R_GAIN_SHIFT ; 
 int /*<<< orphan*/  H2I_DAC_C2 ; 
#define  H2_MIX_INPUT_GAIN 129 
#define  H2_MIX_OUTPUT_ATT 128 
 int hal2_i_read32 (struct snd_hal2*,int /*<<< orphan*/ ) ; 
 struct snd_hal2* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int hal2_gain_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_hal2 *hal2 = snd_kcontrol_chip(kcontrol);
	u32 tmp;
	int l, r;

	switch ((int)kcontrol->private_value) {
	case H2_MIX_OUTPUT_ATT:
		tmp = hal2_i_read32(hal2, H2I_DAC_C2);
		if (tmp & H2I_C2_MUTE) {
			l = 0;
			r = 0;
		} else {
			l = 31 - ((tmp >> H2I_C2_L_ATT_SHIFT) & 31);
			r = 31 - ((tmp >> H2I_C2_R_ATT_SHIFT) & 31);
		}
		break;
	case H2_MIX_INPUT_GAIN:
		tmp = hal2_i_read32(hal2, H2I_ADC_C2);
		l = (tmp >> H2I_C2_L_GAIN_SHIFT) & 15;
		r = (tmp >> H2I_C2_R_GAIN_SHIFT) & 15;
		break;
	default:
		return -EINVAL;
	}
	ucontrol->value.integer.value[0] = l;
	ucontrol->value.integer.value[1] = r;

	return 0;
}
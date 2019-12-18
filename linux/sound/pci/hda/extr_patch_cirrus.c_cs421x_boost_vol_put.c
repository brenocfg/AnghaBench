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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS421X_IDX_SPK_CTL ; 
 unsigned int cs_vendor_coef_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_vendor_coef_set (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int cs421x_boost_vol_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);

	unsigned int vol = ucontrol->value.integer.value[0];
	unsigned int coef =
		cs_vendor_coef_get(codec, CS421X_IDX_SPK_CTL);
	unsigned int original_coef = coef;

	coef &= ~0x0003;
	coef |= (vol & 0x0003);
	if (original_coef == coef)
		return 0;
	else {
		cs_vendor_coef_set(codec, CS421X_IDX_SPK_CTL, coef);
		return 1;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdac_device {int addr; } ;

/* Variables and functions */
 unsigned int AC_AMP_FAKE_MUTE ; 
 unsigned int AC_PWRST_ERROR ; 
 int AC_VERB_GET_POWER_STATE ; 
 int AC_VERB_GET_PROC_COEF ; 
 int AC_VERB_SET_AMP_GAIN_MUTE ; 
 int EAGAIN ; 
 int codec_pm_lock (struct hdac_device*) ; 
 int /*<<< orphan*/  codec_pm_unlock (struct hdac_device*,int) ; 
 int get_verb (unsigned int) ; 
 int hda_reg_read_coef (struct hdac_device*,unsigned int,unsigned int*) ; 
 int hda_reg_read_stereo_amp (struct hdac_device*,unsigned int,unsigned int*) ; 
 scalar_t__ is_stereo_amp_verb (unsigned int) ; 
 int snd_hdac_exec_verb (struct hdac_device*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hda_reg_read(void *context, unsigned int reg, unsigned int *val)
{
	struct hdac_device *codec = context;
	int verb = get_verb(reg);
	int err;
	int pm_lock = 0;

	if (verb != AC_VERB_GET_POWER_STATE) {
		pm_lock = codec_pm_lock(codec);
		if (pm_lock < 0)
			return -EAGAIN;
	}
	reg |= (codec->addr << 28);
	if (is_stereo_amp_verb(reg)) {
		err = hda_reg_read_stereo_amp(codec, reg, val);
		goto out;
	}
	if (verb == AC_VERB_GET_PROC_COEF) {
		err = hda_reg_read_coef(codec, reg, val);
		goto out;
	}
	if ((verb & 0x700) == AC_VERB_SET_AMP_GAIN_MUTE)
		reg &= ~AC_AMP_FAKE_MUTE;

	err = snd_hdac_exec_verb(codec, reg, 0, val);
	if (err < 0)
		goto out;
	/* special handling for asymmetric reads */
	if (verb == AC_VERB_GET_POWER_STATE) {
		if (*val & AC_PWRST_ERROR)
			*val = -1;
		else /* take only the actual state */
			*val = (*val >> 4) & 0x0f;
	}
 out:
	codec_pm_unlock(codec, pm_lock);
	return err;
}
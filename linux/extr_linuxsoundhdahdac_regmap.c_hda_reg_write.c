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
struct hdac_device {int addr; scalar_t__ lazy_cache; scalar_t__ caps_overwriting; } ;

/* Variables and functions */
 unsigned int AC_AMP_FAKE_MUTE ; 
 unsigned int AC_AMP_GET_LEFT ; 
 unsigned int AC_AMP_GET_OUTPUT ; 
 unsigned int AC_AMP_MUTE ; 
 int AC_AMP_SET_INPUT ; 
 int AC_AMP_SET_LEFT ; 
 int AC_AMP_SET_OUTPUT ; 
 int AC_AMP_SET_RIGHT ; 
#define  AC_VERB_SET_AMP_GAIN_MUTE 130 
#define  AC_VERB_SET_CONFIG_DEFAULT_BYTES_0 129 
#define  AC_VERB_SET_DIGI_CONVERT_1 128 
 unsigned int AC_VERB_SET_POWER_STATE ; 
 unsigned int AC_VERB_SET_PROC_COEF ; 
 int EAGAIN ; 
 int codec_pm_lock (struct hdac_device*) ; 
 int /*<<< orphan*/  codec_pm_unlock (struct hdac_device*,int) ; 
 unsigned int get_verb (unsigned int) ; 
 int hda_reg_write_coef (struct hdac_device*,unsigned int,unsigned int) ; 
 int hda_reg_write_stereo_amp (struct hdac_device*,unsigned int,unsigned int) ; 
 scalar_t__ is_stereo_amp_verb (unsigned int) ; 
 int snd_hdac_exec_verb (struct hdac_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hda_reg_write(void *context, unsigned int reg, unsigned int val)
{
	struct hdac_device *codec = context;
	unsigned int verb;
	int i, bytes, err;
	int pm_lock = 0;

	if (codec->caps_overwriting)
		return 0;

	reg &= ~0x00080000U; /* drop GET bit */
	reg |= (codec->addr << 28);
	verb = get_verb(reg);

	if (verb != AC_VERB_SET_POWER_STATE) {
		pm_lock = codec_pm_lock(codec);
		if (pm_lock < 0)
			return codec->lazy_cache ? 0 : -EAGAIN;
	}

	if (is_stereo_amp_verb(reg)) {
		err = hda_reg_write_stereo_amp(codec, reg, val);
		goto out;
	}

	if (verb == AC_VERB_SET_PROC_COEF) {
		err = hda_reg_write_coef(codec, reg, val);
		goto out;
	}

	switch (verb & 0xf00) {
	case AC_VERB_SET_AMP_GAIN_MUTE:
		if ((reg & AC_AMP_FAKE_MUTE) && (val & AC_AMP_MUTE))
			val = 0;
		verb = AC_VERB_SET_AMP_GAIN_MUTE;
		if (reg & AC_AMP_GET_LEFT)
			verb |= AC_AMP_SET_LEFT >> 8;
		else
			verb |= AC_AMP_SET_RIGHT >> 8;
		if (reg & AC_AMP_GET_OUTPUT) {
			verb |= AC_AMP_SET_OUTPUT >> 8;
		} else {
			verb |= AC_AMP_SET_INPUT >> 8;
			verb |= reg & 0xf;
		}
		break;
	}

	switch (verb) {
	case AC_VERB_SET_DIGI_CONVERT_1:
		bytes = 2;
		break;
	case AC_VERB_SET_CONFIG_DEFAULT_BYTES_0:
		bytes = 4;
		break;
	default:
		bytes = 1;
		break;
	}

	for (i = 0; i < bytes; i++) {
		reg &= ~0xfffff;
		reg |= (verb + i) << 8 | ((val >> (8 * i)) & 0xff);
		err = snd_hdac_exec_verb(codec, reg, 0, NULL);
		if (err < 0)
			goto out;
	}

 out:
	codec_pm_unlock(codec, pm_lock);
	return err;
}
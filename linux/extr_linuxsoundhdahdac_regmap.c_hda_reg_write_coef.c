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
struct hdac_device {int /*<<< orphan*/  cache_coef; } ;

/* Variables and functions */
 int AC_VERB_GET_COEF_INDEX ; 
 int AC_VERB_SET_COEF_INDEX ; 
 int EINVAL ; 
 int snd_hdac_exec_verb (struct hdac_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hda_reg_write_coef(struct hdac_device *codec, unsigned int reg,
			      unsigned int val)
{
	unsigned int verb;
	int err;

	if (!codec->cache_coef)
		return -EINVAL;
	/* LSB 8bit = coef index */
	verb = (reg & ~0xfff00) | (AC_VERB_SET_COEF_INDEX << 8);
	err = snd_hdac_exec_verb(codec, verb, 0, NULL);
	if (err < 0)
		return err;
	verb = (reg & ~0xfffff) | (AC_VERB_GET_COEF_INDEX << 8) |
		(val & 0xffff);
	return snd_hdac_exec_verb(codec, verb, 0, NULL);
}
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
struct hdac_device {int caps_overwriting; int /*<<< orphan*/  regmap; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int AC_VERB_PARAMETERS ; 
 int EINVAL ; 
 int snd_hdac_regmap_write_raw (struct hdac_device*,unsigned int,unsigned int) ; 

int snd_hdac_override_parm(struct hdac_device *codec, hda_nid_t nid,
			   unsigned int parm, unsigned int val)
{
	unsigned int verb = (AC_VERB_PARAMETERS << 8) | (nid << 20) | parm;
	int err;

	if (!codec->regmap)
		return -EINVAL;

	codec->caps_overwriting = true;
	err = snd_hdac_regmap_write_raw(codec, verb, val);
	codec->caps_overwriting = false;
	return err;
}
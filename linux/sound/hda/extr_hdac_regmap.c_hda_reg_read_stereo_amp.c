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
struct hdac_device {int dummy; } ;

/* Variables and functions */
 unsigned int AC_AMP_GET_LEFT ; 
 unsigned int AC_AMP_GET_RIGHT ; 
 unsigned int AC_AMP_SET_LEFT ; 
 unsigned int AC_AMP_SET_RIGHT ; 
 int snd_hdac_exec_verb (struct hdac_device*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hda_reg_read_stereo_amp(struct hdac_device *codec,
				   unsigned int reg, unsigned int *val)
{
	unsigned int left, right;
	int err;

	reg &= ~(AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT);
	err = snd_hdac_exec_verb(codec, reg | AC_AMP_GET_LEFT, 0, &left);
	if (err < 0)
		return err;
	err = snd_hdac_exec_verb(codec, reg | AC_AMP_GET_RIGHT, 0, &right);
	if (err < 0)
		return err;
	*val = left | (right << 8);
	return 0;
}
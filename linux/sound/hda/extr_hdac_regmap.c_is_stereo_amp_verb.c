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

/* Variables and functions */
 unsigned int AC_AMP_SET_LEFT ; 
 unsigned int AC_AMP_SET_RIGHT ; 
 unsigned int AC_VERB_SET_AMP_GAIN_MUTE ; 

__attribute__((used)) static bool is_stereo_amp_verb(unsigned int reg)
{
	if (((reg >> 8) & 0x700) != AC_VERB_SET_AMP_GAIN_MUTE)
		return false;
	return (reg & (AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT)) ==
		(AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT);
}
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
 long snd_mixer_oss_conv (long,long,long,long,int) ; 

__attribute__((used)) static long snd_mixer_oss_conv1(long val, long min, long max, int *old)
{
	if (val == snd_mixer_oss_conv(*old, 0, 100, min, max))
		return *old;
	return snd_mixer_oss_conv(val, min, max, 0, 100);
}
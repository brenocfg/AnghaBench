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
struct vx_core {int dummy; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int vx_calc_clock_from_freq(struct vx_core *chip, int freq)
{
	int hexfreq;

	if (snd_BUG_ON(freq <= 0))
		return 0;

	hexfreq = (28224000 * 10) / freq;
	hexfreq = (hexfreq + 5) / 10;

	/* max freq = 55125 Hz */
	if (snd_BUG_ON(hexfreq <= 0x00000200))
		return 0;

	if (hexfreq <= 0x03ff)
		return hexfreq - 0x00000201;
	if (hexfreq <= 0x07ff) 
		return (hexfreq / 2) - 1;
	if (hexfreq <= 0x0fff)
		return (hexfreq / 4) + 0x000001ff;

	return 0x5fe; 	/* min freq = 6893 Hz */
}
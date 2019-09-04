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
struct vx_core {int chip_status; scalar_t__ clock_source; int freq_detected; int /*<<< orphan*/  uer_detected; } ;

/* Variables and functions */
 scalar_t__ INTERNAL_QUARTZ ; 
 int VX_STAT_IS_STALE ; 
 int vx_read_uer_status (struct vx_core*,int /*<<< orphan*/ *) ; 

int vx_change_frequency(struct vx_core *chip)
{
	int freq;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return 0;

	if (chip->clock_source == INTERNAL_QUARTZ)
		return 0;
	/*
	 * Read the real UER board frequency
	 */
	freq = vx_read_uer_status(chip, &chip->uer_detected);
	if (freq < 0)
		return freq;
	/*
	 * The frequency computed by the DSP is good and
	 * is different from the previous computed.
	 */
	if (freq == 48000 || freq == 44100 || freq == 32000)
		chip->freq_detected = freq;

	return 0;
}
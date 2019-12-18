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
typedef  int /*<<< orphan*/  u8 ;
struct snd_galaxy {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_COMMAND_GALAXY_9 ; 
 int dsp_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsp_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int galaxy_set_mode(struct snd_galaxy *galaxy, u8 mode)
{
	int err;

	err = dsp_command(galaxy->port, DSP_COMMAND_GALAXY_9);
	if (err < 0)
		return err;

	err = dsp_command(galaxy->port, mode);
	if (err < 0)
		return err;

#ifdef AZT1605
	/*
	 * Needed for MPU IRQ on AZT1605, but AZT2316 loses WSS again
	 */
	err = dsp_reset(galaxy->port);
	if (err < 0)
		return err;
#endif

	return 0;
}
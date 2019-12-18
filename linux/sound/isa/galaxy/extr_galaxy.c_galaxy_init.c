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
typedef  scalar_t__ u8 ;
struct snd_galaxy {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_COMMAND_GALAXY_8 ; 
 int ENODEV ; 
 int /*<<< orphan*/  GALAXY_COMMAND_GET_TYPE ; 
 scalar_t__ GALAXY_DSP_MAJOR ; 
 scalar_t__ GALAXY_DSP_MINOR ; 
 int dsp_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsp_get_byte (int /*<<< orphan*/ ,scalar_t__*) ; 
 int dsp_get_version (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int dsp_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int galaxy_init(struct snd_galaxy *galaxy, u8 *type)
{
	u8 major;
	u8 minor;
	int err;

	err = dsp_reset(galaxy->port);
	if (err < 0)
		return err;

	err = dsp_get_version(galaxy->port, &major, &minor);
	if (err < 0)
		return err;

	if (major != GALAXY_DSP_MAJOR || minor != GALAXY_DSP_MINOR)
		return -ENODEV;

	err = dsp_command(galaxy->port, DSP_COMMAND_GALAXY_8);
	if (err < 0)
		return err;

	err = dsp_command(galaxy->port, GALAXY_COMMAND_GET_TYPE);
	if (err < 0)
		return err;

	err = dsp_get_byte(galaxy->port, type);
	if (err < 0)
		return err;

	return 0;
}
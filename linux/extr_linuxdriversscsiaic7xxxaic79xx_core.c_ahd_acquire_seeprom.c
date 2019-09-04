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
struct ahd_softc {int dummy; } ;

/* Variables and functions */

int
ahd_acquire_seeprom(struct ahd_softc *ahd)
{
	/*
	 * We should be able to determine the SEEPROM type
	 * from the flexport logic, but unfortunately not
	 * all implementations have this logic and there is
	 * no programatic method for determining if the logic
	 * is present.
	 */
	return (1);
#if 0
	uint8_t	seetype;
	int	error;

	error = ahd_read_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, &seetype);
	if (error != 0
         || ((seetype & FLX_ROMSTAT_SEECFG) == FLX_ROMSTAT_SEE_NONE))
		return (0);
	return (1);
#endif
}
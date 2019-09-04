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
struct vpd_config {int bios_flags; } ;
struct ahd_softc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_BOOT_CHANNEL ; 
 int EINVAL ; 
 int VPDBOOTHOST ; 
 int ahd_verify_vpd_cksum (struct vpd_config*) ; 

int
ahd_parse_vpddata(struct ahd_softc *ahd, struct vpd_config *vpd)
{
	int error;

	error = ahd_verify_vpd_cksum(vpd);
	if (error == 0)
		return (EINVAL);
	if ((vpd->bios_flags & VPDBOOTHOST) != 0)
		ahd->flags |= AHD_BOOT_CHANNEL;
	return (0);
}
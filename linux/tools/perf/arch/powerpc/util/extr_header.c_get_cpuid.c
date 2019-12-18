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
 int ENOBUFS ; 
 int /*<<< orphan*/  PVR_REV (unsigned long) ; 
 int /*<<< orphan*/  PVR_VER (unsigned long) ; 
 int /*<<< orphan*/  SPRN_PVR ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 

int
get_cpuid(char *buffer, size_t sz)
{
	unsigned long pvr;
	int nb;

	pvr = mfspr(SPRN_PVR);

	nb = scnprintf(buffer, sz, "%lu,%lu$", PVR_VER(pvr), PVR_REV(pvr));

	/* look for end marker to ensure the entire data fit */
	if (strchr(buffer, '$')) {
		buffer[nb-1] = '\0';
		return 0;
	}
	return ENOBUFS;
}
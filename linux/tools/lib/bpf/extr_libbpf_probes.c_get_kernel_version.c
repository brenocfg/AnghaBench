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
struct utsname {int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static int get_kernel_version(void)
{
	int version, subversion, patchlevel;
	struct utsname utsn;

	/* Return 0 on failure, and attempt to probe with empty kversion */
	if (uname(&utsn))
		return 0;

	if (sscanf(utsn.release, "%d.%d.%d",
		   &version, &subversion, &patchlevel) != 3)
		return 0;

	return (version << 16) + (subversion << 8) + patchlevel;
}
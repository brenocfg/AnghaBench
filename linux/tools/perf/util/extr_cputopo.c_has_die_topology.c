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
struct utsname {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_SIB_FMT ; 
 int /*<<< orphan*/  F_OK ; 
 int MAXPATHLEN ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sysfs__mountpoint () ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static bool has_die_topology(void)
{
	char filename[MAXPATHLEN];
	struct utsname uts;

	if (uname(&uts) < 0)
		return false;

	if (strncmp(uts.machine, "x86_64", 6))
		return false;

	scnprintf(filename, MAXPATHLEN, DIE_SIB_FMT,
		  sysfs__mountpoint(), 0);
	if (access(filename, F_OK) == -1)
		return false;

	return true;
}
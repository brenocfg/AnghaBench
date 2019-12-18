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
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_ubuntu_kernel_version (unsigned int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ uname (struct utsname*) ; 

int
fetch_kernel_version(unsigned int *puint, char *str,
		     size_t str_size)
{
	struct utsname utsname;
	int version, patchlevel, sublevel, err;
	bool int_ver_ready = false;

	if (access("/proc/version_signature", R_OK) == 0)
		if (!fetch_ubuntu_kernel_version(puint))
			int_ver_ready = true;

	if (uname(&utsname))
		return -1;

	if (str && str_size) {
		strncpy(str, utsname.release, str_size);
		str[str_size - 1] = '\0';
	}

	if (!puint || int_ver_ready)
		return 0;

	err = sscanf(utsname.release, "%d.%d.%d",
		     &version, &patchlevel, &sublevel);

	if (err != 3) {
		pr_debug("Unable to get kernel version from uname '%s'\n",
			 utsname.release);
		return -1;
	}

	*puint = (version << 16) + (patchlevel << 8) + sublevel;
	return 0;
}
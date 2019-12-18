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
struct cache_detail {char* name; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  UMH_WAIT_EXEC ; 
 int call_usermodehelper (char*,char**,char**,int /*<<< orphan*/ ) ; 
 char* nfs_cache_getent_prog ; 

int nfs_cache_upcall(struct cache_detail *cd, char *entry_name)
{
	static char *envp[] = { "HOME=/",
		"TERM=linux",
		"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
		NULL
	};
	char *argv[] = {
		nfs_cache_getent_prog,
		cd->name,
		entry_name,
		NULL
	};
	int ret = -EACCES;

	if (nfs_cache_getent_prog[0] == '\0')
		goto out;
	ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
	/*
	 * Disable the upcall mechanism if we're getting an ENOENT or
	 * EACCES error. The admin can re-enable it on the fly by using
	 * sysfs to set the 'cache_getent' parameter once the problem
	 * has been fixed.
	 */
	if (ret == -ENOENT || ret == -EACCES)
		nfs_cache_getent_prog[0] = '\0';
out:
	return ret > 0 ? 0 : ret;
}
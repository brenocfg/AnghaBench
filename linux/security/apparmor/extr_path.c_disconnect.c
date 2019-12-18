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
struct path {int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int CHROOT_NSCONNECT ; 
 int EACCES ; 
 int PATH_CONNECT_PATH ; 
 scalar_t__ our_mnt (int /*<<< orphan*/ ) ; 
 int prepend (char**,int,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int disconnect(const struct path *path, char *buf, char **name,
		      int flags, const char *disconnected)
{
	int error = 0;

	if (!(flags & PATH_CONNECT_PATH) &&
	    !(((flags & CHROOT_NSCONNECT) == CHROOT_NSCONNECT) &&
	      our_mnt(path->mnt))) {
		/* disconnected path, don't return pathname starting
		 * with '/'
		 */
		error = -EACCES;
		if (**name == '/')
			*name = *name + 1;
	} else {
		if (**name != '/')
			/* CONNECT_PATH with missing root */
			error = prepend(name, *name - buf, "/", 1);
		if (!error && disconnected)
			error = prepend(name, *name - buf, disconnected,
					strlen(disconnected));
	}

	return error;
}
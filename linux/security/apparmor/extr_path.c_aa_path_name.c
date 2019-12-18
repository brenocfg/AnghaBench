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
struct path {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int d_namespace_path (struct path const*,char*,char**,int,char const*) ; 

int aa_path_name(const struct path *path, int flags, char *buffer,
		 const char **name, const char **info, const char *disconnected)
{
	char *str = NULL;
	int error = d_namespace_path(path, buffer, &str, flags, disconnected);

	if (info && error) {
		if (error == -ENOENT)
			*info = "Failed name lookup - deleted entry";
		else if (error == -EACCES)
			*info = "Failed name lookup - disconnected path";
		else if (error == -ENAMETOOLONG)
			*info = "Failed name lookup - name too long";
		else
			*info = "Failed name lookup";
	}

	*name = str;

	return error;
}
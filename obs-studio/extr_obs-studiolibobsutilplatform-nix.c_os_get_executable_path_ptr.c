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
struct dstr {char* array; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PATH_MAX ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int readlink (char*,char*,int) ; 

char *os_get_executable_path_ptr(const char *name)
{
	char exe[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", exe, PATH_MAX);
	const char *path_out = NULL;
	struct dstr path;

	if (count == -1) {
		return NULL;
	}

	path_out = dirname(exe);
	if (!path_out) {
		return NULL;
	}

	dstr_init_copy(&path, path_out);
	dstr_cat(&path, "/");

	if (name && *name) {
		dstr_cat(&path, name);
	}

	return path.array;
}
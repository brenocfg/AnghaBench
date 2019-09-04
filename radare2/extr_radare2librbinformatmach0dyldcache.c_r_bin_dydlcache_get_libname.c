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
struct r_bin_dyldcache_lib_t {char* path; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

void r_bin_dydlcache_get_libname(struct r_bin_dyldcache_lib_t *lib, char **libname) {
	char *cur = lib->path;
	char *res = lib->path;
	int path_length = strlen (lib->path);
	while (cur < cur + path_length - 1) {
		cur = strchr (cur, '/');
		if (!cur) {
			break;
		}
		cur++;
		res = cur;
	}
	*libname = res;
}
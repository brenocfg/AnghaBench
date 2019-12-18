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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*) ; 
 char* r_file_path (char const*) ; 

__attribute__((used)) static void check_decompiler(const char* name) {
	char *path = r_file_path (name);
	if (path && path[0] == '/') {
		r_cons_printf ("!*%s\n", name);
	}
	free (path);
}
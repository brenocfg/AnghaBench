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
typedef  char ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_file_is_directory (char const*) ; 
 scalar_t__ r_stdin_slurp (int*) ; 
 char* r_str_newf (char*,int) ; 
 int rafind_open_dir (char const*) ; 
 int rafind_open_file (char const*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int rafind_open(const char *file) {
	if (!strcmp (file, "-")) {
		int sz = 0;
		ut8 *buf = (ut8 *)r_stdin_slurp (&sz);
		char *ff = r_str_newf ("malloc://%d", sz);
		int res = rafind_open_file (ff, buf, sz);
		free (ff);
		free (buf);
		return res;
	}
	return r_file_is_directory (file)
		? rafind_open_dir (file)
		: rafind_open_file (file, NULL, -1);
}
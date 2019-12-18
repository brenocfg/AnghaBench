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
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_file_path (char const*) ; 
 char* r_sys_getenv (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char* r_egg_Cfile_getCompiler(void) {
	size_t i;
	const char *compilers[] = {"llvm-gcc", "clang", "gcc"};
	char *output = r_sys_getenv ("CC");

	if (output) {
		return output;
	}

	for (i = 0; i < 3; i++) {
		output = r_file_path (compilers[i]);
		if (strcmp (output, compilers[i])) {
			free (output);
			return strdup (compilers[i]);
		}
		free (output);
	}

	eprintf ("Couldn't find a compiler ! Please, set CC.\n");
	return NULL;
}
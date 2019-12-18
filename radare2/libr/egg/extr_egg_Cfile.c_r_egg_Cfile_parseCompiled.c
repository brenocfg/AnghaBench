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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_file_dump (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 char* r_file_slurp (char*,int /*<<< orphan*/ *) ; 
 char* r_str_newf (char*,char const*) ; 
 char* r_str_replace (char*,char*,char*,int) ; 
 int /*<<< orphan*/  r_str_stripLine (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool r_egg_Cfile_parseCompiled(const char *file) {
	char *fileExt = r_str_newf ("%s.tmp", file);
	char *buffer = r_file_slurp (fileExt, NULL);

	buffer = r_str_replace (buffer, "rdata", "text", false);
	buffer = r_str_replace (buffer, "rodata", "text", false);
	buffer = r_str_replace (buffer, "get_pc_thunk.bx", "__getesp__", true);

	const char *words[] = {".cstring", "size", "___main", "section", "__alloca", "zero", "cfi"};
	size_t i;
	for (i = 0; i < 7; i++) {
		r_str_stripLine (buffer, words[i]);
	}

	free (fileExt);
	fileExt = r_str_newf ("%s.s", file);
	if (!r_file_dump (fileExt, (const ut8*) buffer, strlen (buffer), true)) {
		eprintf ("Error while opening %s.s\n", file);
		goto fail;
	}

	free (buffer);
	free (fileExt);
	return true;

fail:
	free (buffer);
	free (fileExt);
	return false;
}
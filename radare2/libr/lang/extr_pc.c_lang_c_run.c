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
typedef  int /*<<< orphan*/  RLang ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_c_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 

__attribute__((used)) static int lang_c_run(RLang *lang, const char *code, int len) {
	FILE *fd = r_sandbox_fopen (".tmp.c", "w");
	if (fd) {
		fputs ("#include <r_core.h>\n\nvoid entry(RCore *core, int argc, const char **argv) {\n", fd);
		fputs (code, fd);
		fputs ("\n}\n", fd);
		fclose (fd);
		lang_c_file (lang, ".tmp.c");
		r_file_rm (".tmp.c");
	} else eprintf ("Cannot open .tmp.c\n");
	return true;
}
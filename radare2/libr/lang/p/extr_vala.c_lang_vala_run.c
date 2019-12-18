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
 int /*<<< orphan*/  lang_vala_file (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int lang_vala_run(RLang *lang, const char *code, int len) {
	bool silent = !strncmp (code, "-s", 2);
	FILE *fd = r_sandbox_fopen (".tmp.vala", "w");
	if (fd) {
		if (silent) {
			code += 2;
		}
		fputs ("using Radare;\n\npublic static void entry(RCore core) {\n", fd);
		fputs (code, fd);
		fputs (";\n}\n", fd);
		fclose (fd);
		lang_vala_file (lang, ".tmp.vala", silent);
		r_file_rm (".tmp.vala");
		return true;
	}
	eprintf ("Cannot open .tmp.vala\n");
	return false;
}
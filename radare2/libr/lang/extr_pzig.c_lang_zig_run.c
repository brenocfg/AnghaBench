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
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_zig_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_file_rm (char const*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char const*,char*) ; 

__attribute__((used)) static int lang_zig_run(RLang *lang, const char *code, int len) {
	const char *file = "_tmp.zig";
	FILE *fd = r_sandbox_fopen (file, "w");
	if (fd) {
		const char *zig_header = \
"extern fn puts(&const u8) void;\n" \
"extern fn r_core_cmd_str(&u8, &const u8) &u8;\n" \
"extern fn r_core_new() &u8;\n" \
"extern fn r_core_free(&u8) void;\n" \
"\n" \
"export fn entry(core: &u8) void {\n";
		const char *zig_footer = \
"\n}\n" \
"pub fn r2cmd(core: &u8, cmd: u8) &u8 {\n" \
"  return r_core_cmd_str(core, cmd);\n" \
"}\n";
		fputs (zig_header, fd);
		fputs (code, fd);
		fputs (zig_footer, fd);
		fclose (fd);
		lang_zig_file (lang, file);
		r_file_rm (file);
	} else {
		eprintf ("Cannot open %s\n", file);
	}
	return true;
}
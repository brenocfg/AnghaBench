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
 int /*<<< orphan*/  lang_cpipe_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 

__attribute__((used)) static int lang_cpipe_run(RLang *lang, const char *code, int len) {
	FILE *fd = r_sandbox_fopen (".tmp.c", "w");
	if (fd) {
		eprintf ("Cannot open .tmp.c\n");
		return false;
	}
	fputs ("#include <r_socket.h>\n\n"
		"#define R2P(x,y...) r2pipe_cmdf(r2p,x,##y)\n"
		"int main() {\n"
		"  R2Pipe *r2p = r2pipe_open(NULL);", fd);
	fputs (code, fd);
	fputs ("\n}\n", fd);
	fclose (fd);
	lang_cpipe_file (lang, ".tmp.c");
	r_file_rm (".tmp.c");
	return true;
}
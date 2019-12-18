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
 int /*<<< orphan*/  lang_v_file (int /*<<< orphan*/ *,char*) ; 
 char* r2v ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 
 char* vsk ; 

__attribute__((used)) static int __run(RLang *lang, const char *code, int len) {
	FILE *fd = r_sandbox_fopen (".tmp.v", "w");
	if (fd) {
		fputs (r2v, fd);
		if (len < 0) {
			fputs (code, fd);
		} else {
			fputs (vsk, fd);
			fputs (code, fd);
			fputs ("}", fd);
		}
		fclose (fd);
		lang_v_file (lang, ".tmp.v");
		r_file_rm (".tmp.v");
		return true;
	}
	eprintf ("Cannot open .tmp.v\n");
	return false;
}
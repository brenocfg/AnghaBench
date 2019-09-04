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
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int code ; 
 int /*<<< orphan*/  command (char*,char const*) ; 
 scalar_t__ confirm (char const*,char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 int interactive ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  makeargv () ; 
 int margc ; 
 char** margv ; 
 int mflag ; 
 char const* mname ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* remglob (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

void mdelete(int argc, const char *argv[])
{
	const char *cp;
	int ointer;
	extern jmp_buf jabort;

	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(remote-files) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s remote-files\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	mname = argv[0];
	mflag = 1;
//	oldintr = signal(SIGINT, mabort);
	(void) setjmp(jabort);
	while ((cp = remglob(argv,0)) != NULL) {
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && confirm(argv[0], cp)) {
			(void) command("DELE %s", cp);
			if (!mflag && fromatty) {
				ointer = interactive;
				interactive = 1;
				if (confirm("Continue with", "mdelete")) {
					mflag++;
				}
				interactive = ointer;
			}
		}
	}
//	(void) signal(SIGINT, oldintr);
	mflag = 0;
}
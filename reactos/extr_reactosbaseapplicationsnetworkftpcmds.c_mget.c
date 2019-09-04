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
 int MAXPATHLEN ; 
 int code ; 
 scalar_t__ confirm (char const*,char const*) ; 
 char* domap (char const*) ; 
 char* dotrans (char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 int interactive ; 
 int /*<<< orphan*/  islower (char const) ; 
 scalar_t__ isupper (char) ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  makeargv () ; 
 scalar_t__ mapflag ; 
 int margc ; 
 char** margv ; 
 scalar_t__ mcase ; 
 int mflag ; 
 char const* mname ; 
 scalar_t__ ntflag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proxy ; 
 int /*<<< orphan*/  recvrequest (char*,char const*,char const*,char*,int) ; 
 char* remglob (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

void mget(int argc, const char *argv[])
{
	const char *cp, *tp;
    char *tp2, tmpbuf[MAXPATHLEN];
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
//	oldintr = signal(SIGINT,mabort);
	(void) setjmp(jabort);
	while ((cp = remglob(argv,proxy)) != NULL) {
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && confirm(argv[0], cp)) {
			tp = cp;
			if (mcase) {
				while (*tp && !islower(*tp)) {
					tp++;
				}
				if (!*tp) {
					tp = cp;
					tp2 = tmpbuf;
					while ((*tp2 = *tp)) {
						if (isupper(*tp2)) {
							*tp2 = 'a' + *tp2 - 'A';
						}
						tp++;
						tp2++;
					}
				}
				tp = tmpbuf;
			}
			if (ntflag) {
				tp = dotrans(tp);
			}
			if (mapflag) {
				tp = domap(tp);
			}
			recvrequest("RETR", tp, cp, "w",
			    tp != cp || !interactive);
			if (!mflag && fromatty) {
				ointer = interactive;
				interactive = 1;
				if (confirm("Continue with","mget")) {
					mflag++;
				}
				interactive = ointer;
			}
		}
	}
//	(void) signal(SIGINT,oldintr);
	mflag = 0;
}
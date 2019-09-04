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
 int /*<<< orphan*/  blkfree (char**) ; 
 int code ; 
 scalar_t__ confirm (char const*,char const*) ; 
 int /*<<< orphan*/  doglob ; 
 char const* domap (char const*) ; 
 char* dotrans (char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fromatty ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 char** glob (char const*) ; 
 char* globerr ; 
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
 scalar_t__ proxy ; 
 char* remglob (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendrequest (char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ sunique ; 

void mput(int argc, const char *argv[])
{
	register int i;
	int ointer;
	extern jmp_buf jabort;
	const char *tp;

	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(local-files) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s local-files\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	mname = argv[0];
	mflag = 1;
//	oldintr = signal(SIGINT, mabort);
	(void) setjmp(jabort);
	if (proxy) {
		const char *cp;
		char *tp2, tmpbuf[MAXPATHLEN];

		while ((cp = remglob(argv,0)) != NULL) {
			if (*cp == 0) {
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
				sendrequest((sunique) ? "STOU" : "STOR",
				    cp, tp, cp != tp || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
//		(void) signal(SIGINT, oldintr);
		mflag = 0;
		return;
	}
	for (i = 1; i < argc; i++) {
		register char **cpp, **gargs;

		if (!doglob) {
			if (mflag && confirm(argv[0], argv[i])) {
				tp = (ntflag) ? dotrans(argv[i]) : argv[i];
				tp = (mapflag) ? domap(tp) : tp;
				sendrequest((sunique) ? "STOU" : "STOR",
				    argv[i], tp, tp != argv[i] || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
			continue;
		}
		gargs = glob(argv[i]);
		if (globerr != NULL) {
			printf("%s\n", globerr);
			(void) fflush(stdout);
			if (gargs) {
				blkfree(gargs);
				free((char *)gargs);
			}
			continue;
		}
		for (cpp = gargs; cpp && *cpp != NULL; cpp++) {
			if (mflag && confirm(argv[0], *cpp)) {
				tp = (ntflag) ? dotrans(*cpp) : *cpp;
				tp = (mapflag) ? domap(tp) : tp;
				sendrequest((sunique) ? "STOU" : "STOR",
				    *cpp, tp, *cpp != tp || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
		if (gargs != NULL) {
			blkfree(gargs);
			free((char *)gargs);
		}
	}
//	(void) signal(SIGINT, oldintr);
	mflag = 0;
}
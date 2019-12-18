#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct servent {int /*<<< orphan*/  s_port; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {char* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORM_N ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MODE_S ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  SO_DEBUG ; 
 int /*<<< orphan*/  STRU_F ; 
 int /*<<< orphan*/  TYPE_A ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _fmode ; 
 int autologin ; 
 char* bytename ; 
 int bytesize ; 
 int /*<<< orphan*/  cmdscanner (int) ; 
 scalar_t__ cpend ; 
 int crflag ; 
 int /*<<< orphan*/  debug ; 
 int doglob ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  form ; 
 char* formname ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fromatty ; 
 char* getlogin () ; 
 TYPE_1__* getpwnam (char const*) ; 
 TYPE_1__* getpwuid (int /*<<< orphan*/ ) ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  getuid () ; 
 char* home ; 
 int interactive ; 
 int /*<<< orphan*/  mode ; 
 char* modename ; 
 int /*<<< orphan*/  options ; 
 int passivemode ; 
 int /*<<< orphan*/  portnum ; 
 scalar_t__ proxy ; 
 TYPE_1__* pw ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpeer (int,char const**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcpy (char*,char*) ; 
 int /*<<< orphan*/  stru ; 
 char* structname ; 
 int /*<<< orphan*/  toplevel ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  type ; 
 char* typename ; 
 int /*<<< orphan*/  verbose ; 

int main(int argc, const char *argv[])
{
	const char *cp;
	int top;
#if 0
	char homedir[MAXPATHLEN];
#endif

        int err;
        WORD wVerReq;

        WSADATA WSAData;
        struct	servent *sp;		/* service spec for tcp/ftp */

	/* Disable output buffering, for the benefit of Emacs.  */
	//setbuf(stdout, NULL);

        _fmode = O_BINARY; // This causes an error somewhere.

        wVerReq = MAKEWORD(1,1);

        err = WSAStartup(wVerReq, &WSAData);
        if (err != 0)
        {
           fprintf(stderr, "Could not initialize Windows socket interface.");
           exit(1);
        }

	sp = getservbyname("ftp", "tcp");
	if (sp == 0) {
		fprintf(stderr, "ftp: ftp/tcp: unknown service\n");
		exit(1);
	}

        portnum = sp->s_port;


	doglob = 1;
	interactive = 1;
	autologin = 1;
	argc--, argv++;
	while (argc > 0 && **argv == '-') {
		for (cp = *argv + 1; *cp; cp++)
			switch (*cp) {

			case 'd':
				options |= SO_DEBUG;
				debug++;
				break;

			case 'v':
				verbose++;
				break;

			case 't':
				trace++;
				break;

			case 'i':
				interactive = 0;
				break;

			case 'n':
				autologin = 0;
				break;

			case 'g':
				doglob = 0;
				break;

			default:
				fprintf(stdout,
				  "ftp: %c: unknown option\n", *cp);
				exit(1);
			}
		argc--, argv++;
	}
//	fromatty = isatty(fileno(stdin));
        fromatty = 1; // Strengthen this test
	/*
	 * Set up defaults for FTP.
	 */
	(void) strcpy(typename, "ascii"), type = TYPE_A;
	(void) strcpy(formname, "non-print"), form = FORM_N;
	(void) strcpy(modename, "stream"), mode = MODE_S;
	(void) strcpy(structname, "file"), stru = STRU_F;
	(void) strcpy(bytename, "8"), bytesize = 8;
	if (fromatty)
		verbose++;
	cpend = 0;           /* no pending replies */
	proxy = 0;	/* proxy not active */
    passivemode = 1; /* passive mode *is* active */
	crflag = 1;    /* strip c.r. on ascii gets */
	/*
	 * Set up the home directory in case we're globbing.
	 */
#if 0
	cp = getlogin();
	if (cp != NULL) {
		pw = getpwnam(cp);
	}
	if (pw == NULL)
		pw = getpwuid(getuid());
	if (pw != NULL) {
		home = homedir;
		(void) strcpy(home, pw->pw_dir);
	}
#endif
        strcpy(home, "C:/");
	if (argc > 0) {
		if (setjmp(toplevel))
			exit(0);
//		(void) signal(SIGINT, intr);
//		(void) signal(SIGPIPE, lostpeer);
		setpeer(argc + 1, argv - 1);
	}
	top = setjmp(toplevel) == 0;
	if (top) {
//		(void) signal(SIGINT, intr);
//		(void) signal(SIGPIPE, lostpeer);
	}
	for (;;) {
		cmdscanner(top);
		top = 1;
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  AuxiliaryProcessMain (int,char**) ; 
 int /*<<< orphan*/  GucInfoMain () ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LC_MONETARY ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  MemoryContextInit () ; 
 int /*<<< orphan*/  PG_BACKEND_VERSIONSTR ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  PostgresMain (int,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostmasterMain (int,char**) ; 
 int /*<<< orphan*/  SubPostmasterMain (int,char**) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  check_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_strxfrm_bug () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_progname (char*) ; 
 int /*<<< orphan*/  get_user_name_or_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_locale (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pgwin32_install_crashdump_handler () ; 
 int /*<<< orphan*/  pgwin32_signal_initialize () ; 
 int /*<<< orphan*/  progname ; 
 char** save_ps_display_args (int,char**) ; 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startup_hacks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

int
main(int argc, char *argv[])
{
	bool		do_check_root = true;

	/*
	 * If supported on the current platform, set up a handler to be called if
	 * the backend/postmaster crashes with a fatal signal or exception.
	 */
#if defined(WIN32) && defined(HAVE_MINIDUMP_TYPE)
	pgwin32_install_crashdump_handler();
#endif

	progname = get_progname(argv[0]);

	/*
	 * Platform-specific startup hacks
	 */
	startup_hacks(progname);

	/*
	 * Remember the physical location of the initially given argv[] array for
	 * possible use by ps display.  On some platforms, the argv[] storage must
	 * be overwritten in order to set the process title for ps. In such cases
	 * save_ps_display_args makes and returns a new copy of the argv[] array.
	 *
	 * save_ps_display_args may also move the environment strings to make
	 * extra room. Therefore this should be done as early as possible during
	 * startup, to avoid entanglements with code that might save a getenv()
	 * result pointer.
	 */
	argv = save_ps_display_args(argc, argv);

	/*
	 * Fire up essential subsystems: error and memory management
	 *
	 * Code after this point is allowed to use elog/ereport, though
	 * localization of messages may not work right away, and messages won't go
	 * anywhere but stderr until GUC settings get loaded.
	 */
	MemoryContextInit();

	/*
	 * Set up locale information
	 */
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("postgres"));

	/*
	 * In the postmaster, absorb the environment values for LC_COLLATE and
	 * LC_CTYPE.  Individual backends will change these later to settings
	 * taken from pg_database, but the postmaster cannot do that.  If we leave
	 * these set to "C" then message localization might not work well in the
	 * postmaster.
	 */
	init_locale("LC_COLLATE", LC_COLLATE, "");
	init_locale("LC_CTYPE", LC_CTYPE, "");

	/*
	 * LC_MESSAGES will get set later during GUC option processing, but we set
	 * it here to allow startup error messages to be localized.
	 */
#ifdef LC_MESSAGES
	init_locale("LC_MESSAGES", LC_MESSAGES, "");
#endif

	/*
	 * We keep these set to "C" always, except transiently in pg_locale.c; see
	 * that file for explanations.
	 */
	init_locale("LC_MONETARY", LC_MONETARY, "C");
	init_locale("LC_NUMERIC", LC_NUMERIC, "C");
	init_locale("LC_TIME", LC_TIME, "C");

	/*
	 * Now that we have absorbed as much as we wish to from the locale
	 * environment, remove any LC_ALL setting, so that the environment
	 * variables installed by pg_perm_setlocale have force.
	 */
	unsetenv("LC_ALL");

	check_strxfrm_bug();

	/*
	 * Catch standard options before doing much else, in particular before we
	 * insist on not being root.
	 */
	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
		{
			help(progname);
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			fputs(PG_BACKEND_VERSIONSTR, stdout);
			exit(0);
		}

		/*
		 * In addition to the above, we allow "--describe-config" and "-C var"
		 * to be called by root.  This is reasonably safe since these are
		 * read-only activities.  The -C case is important because pg_ctl may
		 * try to invoke it while still holding administrator privileges on
		 * Windows.  Note that while -C can normally be in any argv position,
		 * if you want to bypass the root check you must put it first.  This
		 * reduces the risk that we might misinterpret some other mode's -C
		 * switch as being the postmaster/postgres one.
		 */
		if (strcmp(argv[1], "--describe-config") == 0)
			do_check_root = false;
		else if (argc > 2 && strcmp(argv[1], "-C") == 0)
			do_check_root = false;
	}

	/*
	 * Make sure we are not running as root, unless it's safe for the selected
	 * option.
	 */
	if (do_check_root)
		check_root(progname);

	/*
	 * Dispatch to one of various subprograms depending on first argument.
	 */

#ifdef EXEC_BACKEND
	if (argc > 1 && strncmp(argv[1], "--fork", 6) == 0)
		SubPostmasterMain(argc, argv);	/* does not return */
#endif

#ifdef WIN32

	/*
	 * Start our win32 signal implementation
	 *
	 * SubPostmasterMain() will do this for itself, but the remaining modes
	 * need it here
	 */
	pgwin32_signal_initialize();
#endif

	if (argc > 1 && strcmp(argv[1], "--boot") == 0)
		AuxiliaryProcessMain(argc, argv);	/* does not return */
	else if (argc > 1 && strcmp(argv[1], "--describe-config") == 0)
		GucInfoMain();			/* does not return */
	else if (argc > 1 && strcmp(argv[1], "--single") == 0)
		PostgresMain(argc, argv,
					 NULL,		/* no dbname */
					 strdup(get_user_name_or_exit(progname)));	/* does not return */
	else
		PostmasterMain(argc, argv); /* does not return */
	abort();					/* should not get here */
}
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
typedef  int /*<<< orphan*/  PerlInterpreter ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  FloatExceptionHandler ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MONETARY ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  LC_TIME ; 
 size_t OP_DOFILE ; 
 size_t OP_REQUIRE ; 
 int /*<<< orphan*/  PERL_EXIT_DESTRUCT_END ; 
 int /*<<< orphan*/  PERL_SET_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PERL_SYS_INIT3 (int*,char***,char***) ; 
#define  PLC_PERLBOOT 128 
 int /*<<< orphan*/  PLPERL_RESTORE_LOCALE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PL_exit_flags ; 
 int /*<<< orphan*/  PL_op_mask ; 
 scalar_t__* PL_ppaddr ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * perl_alloc () ; 
 int /*<<< orphan*/  perl_construct (int /*<<< orphan*/ *) ; 
 scalar_t__ perl_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ perl_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plperl_init_shared_libs ; 
 char* plperl_on_init ; 
 int /*<<< orphan*/  plperl_opmask ; 
 scalar_t__ pp_require_orig ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 char* setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PerlInterpreter *
plperl_init_interp(void)
{
	PerlInterpreter *plperl;

	static char *embedding[3 + 2] = {
		"", "-e", PLC_PERLBOOT
	};
	int			nargs = 3;

#ifdef WIN32

	/*
	 * The perl library on startup does horrible things like call
	 * setlocale(LC_ALL,""). We have protected against that on most platforms
	 * by setting the environment appropriately. However, on Windows,
	 * setlocale() does not consult the environment, so we need to save the
	 * existing locale settings before perl has a chance to mangle them and
	 * restore them after its dirty deeds are done.
	 *
	 * MSDN ref:
	 * http://msdn.microsoft.com/library/en-us/vclib/html/_crt_locale.asp
	 *
	 * It appears that we only need to do this on interpreter startup, and
	 * subsequent calls to the interpreter don't mess with the locale
	 * settings.
	 *
	 * We restore them using setlocale_perl(), defined below, so that Perl
	 * doesn't have a different idea of the locale from Postgres.
	 *
	 */

	char	   *loc;
	char	   *save_collate,
			   *save_ctype,
			   *save_monetary,
			   *save_numeric,
			   *save_time;

	loc = setlocale(LC_COLLATE, NULL);
	save_collate = loc ? pstrdup(loc) : NULL;
	loc = setlocale(LC_CTYPE, NULL);
	save_ctype = loc ? pstrdup(loc) : NULL;
	loc = setlocale(LC_MONETARY, NULL);
	save_monetary = loc ? pstrdup(loc) : NULL;
	loc = setlocale(LC_NUMERIC, NULL);
	save_numeric = loc ? pstrdup(loc) : NULL;
	loc = setlocale(LC_TIME, NULL);
	save_time = loc ? pstrdup(loc) : NULL;

#define PLPERL_RESTORE_LOCALE(name, saved) \
	STMT_START { \
		if (saved != NULL) { setlocale_perl(name, saved); pfree(saved); } \
	} STMT_END
#endif							/* WIN32 */

	if (plperl_on_init && *plperl_on_init)
	{
		embedding[nargs++] = "-e";
		embedding[nargs++] = plperl_on_init;
	}

	/*
	 * The perl API docs state that PERL_SYS_INIT3 should be called before
	 * allocating interpreters. Unfortunately, on some platforms this fails in
	 * the Perl_do_taint() routine, which is called when the platform is using
	 * the system's malloc() instead of perl's own. Other platforms, notably
	 * Windows, fail if PERL_SYS_INIT3 is not called. So we call it if it's
	 * available, unless perl is using the system malloc(), which is true when
	 * MYMALLOC is set.
	 */
#if defined(PERL_SYS_INIT3) && !defined(MYMALLOC)
	{
		static int	perl_sys_init_done;

		/* only call this the first time through, as per perlembed man page */
		if (!perl_sys_init_done)
		{
			char	   *dummy_env[1] = {NULL};

			PERL_SYS_INIT3(&nargs, (char ***) &embedding, (char ***) &dummy_env);

			/*
			 * For unclear reasons, PERL_SYS_INIT3 sets the SIGFPE handler to
			 * SIG_IGN.  Aside from being extremely unfriendly behavior for a
			 * library, this is dumb on the grounds that the results of a
			 * SIGFPE in this state are undefined according to POSIX, and in
			 * fact you get a forced process kill at least on Linux.  Hence,
			 * restore the SIGFPE handler to the backend's standard setting.
			 * (See Perl bug 114574 for more information.)
			 */
			pqsignal(SIGFPE, FloatExceptionHandler);

			perl_sys_init_done = 1;
			/* quiet warning if PERL_SYS_INIT3 doesn't use the third argument */
			dummy_env[0] = NULL;
		}
	}
#endif

	plperl = perl_alloc();
	if (!plperl)
		elog(ERROR, "could not allocate Perl interpreter");

	PERL_SET_CONTEXT(plperl);
	perl_construct(plperl);

	/*
	 * Run END blocks in perl_destruct instead of perl_run.  Note that dTHX
	 * loads up a pointer to the current interpreter, so we have to postpone
	 * it to here rather than put it at the function head.
	 */
	{
		dTHX;

		PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

		/*
		 * Record the original function for the 'require' and 'dofile'
		 * opcodes.  (They share the same implementation.)  Ensure it's used
		 * for new interpreters.
		 */
		if (!pp_require_orig)
			pp_require_orig = PL_ppaddr[OP_REQUIRE];
		else
		{
			PL_ppaddr[OP_REQUIRE] = pp_require_orig;
			PL_ppaddr[OP_DOFILE] = pp_require_orig;
		}

#ifdef PLPERL_ENABLE_OPMASK_EARLY

		/*
		 * For regression testing to prove that the PLC_PERLBOOT and
		 * PLC_TRUSTED code doesn't even compile any unsafe ops.  In future
		 * there may be a valid need for them to do so, in which case this
		 * could be softened (perhaps moved to plperl_trusted_init()) or
		 * removed.
		 */
		PL_op_mask = plperl_opmask;
#endif

		if (perl_parse(plperl, plperl_init_shared_libs,
					   nargs, embedding, NULL) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
					 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
					 errcontext("while parsing Perl initialization")));

		if (perl_run(plperl) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
					 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
					 errcontext("while running Perl initialization")));

#ifdef PLPERL_RESTORE_LOCALE
		PLPERL_RESTORE_LOCALE(LC_COLLATE, save_collate);
		PLPERL_RESTORE_LOCALE(LC_CTYPE, save_ctype);
		PLPERL_RESTORE_LOCALE(LC_MONETARY, save_monetary);
		PLPERL_RESTORE_LOCALE(LC_NUMERIC, save_numeric);
		PLPERL_RESTORE_LOCALE(LC_TIME, save_time);
#endif
	}

	return plperl;
}
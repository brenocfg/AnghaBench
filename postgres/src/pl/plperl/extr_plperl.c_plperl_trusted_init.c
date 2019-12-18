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
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  I32 ;
typedef  int /*<<< orphan*/  HV ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GV_ADDWARN ; 
 int /*<<< orphan*/  GvCV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GvCV_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t OP_DOFILE ; 
 size_t OP_REQUIRE ; 
 char* PLC_TRUSTED ; 
 int /*<<< orphan*/  PL_op_mask ; 
 int /*<<< orphan*/ * PL_ppaddr ; 
 int /*<<< orphan*/ * PL_stashcache ; 
 int /*<<< orphan*/  PL_sub_generation ; 
 int /*<<< orphan*/  SvREFCNT_dec (int /*<<< orphan*/ ) ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_pv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gv_stashpv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_iterinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hv_iternextsv (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isGV_with_GP (int /*<<< orphan*/ *) ; 
 char* plperl_on_plperl_init ; 
 int /*<<< orphan*/  plperl_opmask ; 
 int /*<<< orphan*/  pp_require_orig ; 
 int /*<<< orphan*/  pp_require_safe ; 
 int /*<<< orphan*/  strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plperl_trusted_init(void)
{
	dTHX;
	HV		   *stash;
	SV		   *sv;
	char	   *key;
	I32			klen;

	/* use original require while we set up */
	PL_ppaddr[OP_REQUIRE] = pp_require_orig;
	PL_ppaddr[OP_DOFILE] = pp_require_orig;

	eval_pv(PLC_TRUSTED, FALSE);
	if (SvTRUE(ERRSV))
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
				 errcontext("while executing PLC_TRUSTED")));

	/*
	 * Force loading of utf8 module now to prevent errors that can arise from
	 * the regex code later trying to load utf8 modules. See
	 * http://rt.perl.org/rt3/Ticket/Display.html?id=47576
	 */
	eval_pv("my $a=chr(0x100); return $a =~ /\\xa9/i", FALSE);
	if (SvTRUE(ERRSV))
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
				 errcontext("while executing utf8fix")));

	/*
	 * Lock down the interpreter
	 */

	/* switch to the safe require/dofile opcode for future code */
	PL_ppaddr[OP_REQUIRE] = pp_require_safe;
	PL_ppaddr[OP_DOFILE] = pp_require_safe;

	/*
	 * prevent (any more) unsafe opcodes being compiled PL_op_mask is per
	 * interpreter, so this only needs to be set once
	 */
	PL_op_mask = plperl_opmask;

	/* delete the DynaLoader:: namespace so extensions can't be loaded */
	stash = gv_stashpv("DynaLoader", GV_ADDWARN);
	hv_iterinit(stash);
	while ((sv = hv_iternextsv(stash, &key, &klen)))
	{
		if (!isGV_with_GP(sv) || !GvCV(sv))
			continue;
		SvREFCNT_dec(GvCV(sv)); /* free the CV */
		GvCV_set(sv, NULL);		/* prevent call via GV */
	}
	hv_clear(stash);

	/* invalidate assorted caches */
	++PL_sub_generation;
	hv_clear(PL_stashcache);

	/*
	 * Execute plperl.on_plperl_init in the locked-down interpreter
	 */
	if (plperl_on_plperl_init && *plperl_on_plperl_init)
	{
		eval_pv(plperl_on_plperl_init, FALSE);
		/* XXX need to find a way to determine a better errcode here */
		if (SvTRUE(ERRSV))
			ereport(ERROR,
					(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
					 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
					 errcontext("while executing plperl.on_plperl_init")));
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reference; } ;
typedef  TYPE_1__ plperl_proc_desc ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  FREETMPS ; 
 int G_EVAL ; 
 int G_SCALAR ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  POPs ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTBACK ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SPAGAIN ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dSP ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * get_sv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newSVsv (int /*<<< orphan*/ ) ; 
 int perl_call_sv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp ; 
 int /*<<< orphan*/  strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_setsv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
plperl_call_perl_event_trigger_func(plperl_proc_desc *desc,
									FunctionCallInfo fcinfo,
									SV *td)
{
	dTHX;
	dSP;
	SV		   *retval,
			   *TDsv;
	int			count;

	ENTER;
	SAVETMPS;

	TDsv = get_sv("main::_TD", 0);
	if (!TDsv)
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("couldn't fetch $_TD")));

	save_item(TDsv);			/* local $_TD */
	sv_setsv(TDsv, td);

	PUSHMARK(sp);
	PUTBACK;

	/* Do NOT use G_KEEPERR here */
	count = perl_call_sv(desc->reference, G_SCALAR | G_EVAL);

	SPAGAIN;

	if (count != 1)
	{
		PUTBACK;
		FREETMPS;
		LEAVE;
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("didn't get a return item from trigger function")));
	}

	if (SvTRUE(ERRSV))
	{
		(void) POPs;
		PUTBACK;
		FREETMPS;
		LEAVE;
		/* XXX need to find a way to determine a better errcode here */
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV)))));
	}

	retval = newSVsv(POPs);
	(void) retval;				/* silence compiler warning */

	PUTBACK;
	FREETMPS;
	LEAVE;

	return;
}
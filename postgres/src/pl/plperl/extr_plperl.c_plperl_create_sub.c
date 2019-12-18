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
struct TYPE_3__ {char* proname; int /*<<< orphan*/ * reference; } ;
typedef  TYPE_1__ plperl_proc_desc ;
typedef  int /*<<< orphan*/  SV ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HV ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  EXTEND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FREETMPS ; 
 int G_EVAL ; 
 int G_KEEPERR ; 
 int G_SCALAR ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  PL_sv_no ; 
 scalar_t__ POPs ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PUTBACK ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  SPAGAIN ; 
 scalar_t__ SVt_PVCV ; 
 scalar_t__ SvROK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvRV (int /*<<< orphan*/ *) ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 scalar_t__ SvTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr2sv (char const*) ; 
 int /*<<< orphan*/  dSP ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  hv_store_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newRV_noinc (int /*<<< orphan*/ *) ; 
 int perl_call_pv (char*,int) ; 
 scalar_t__ plperl_use_strict ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 char* strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sv_2mortal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plperl_create_sub(plperl_proc_desc *prodesc, const char *s, Oid fn_oid)
{
	dTHX;
	dSP;
	char		subname[NAMEDATALEN + 40];
	HV		   *pragma_hv = newHV();
	SV		   *subref = NULL;
	int			count;

	sprintf(subname, "%s__%u", prodesc->proname, fn_oid);

	if (plperl_use_strict)
		hv_store_string(pragma_hv, "strict", (SV *) newAV());

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	EXTEND(SP, 4);
	PUSHs(sv_2mortal(cstr2sv(subname)));
	PUSHs(sv_2mortal(newRV_noinc((SV *) pragma_hv)));

	/*
	 * Use 'false' for $prolog in mkfunc, which is kept for compatibility in
	 * case a module such as PostgreSQL::PLPerl::NYTprof replaces the function
	 * compiler.
	 */
	PUSHs(&PL_sv_no);
	PUSHs(sv_2mortal(cstr2sv(s)));
	PUTBACK;

	/*
	 * G_KEEPERR seems to be needed here, else we don't recognize compile
	 * errors properly.  Perhaps it's because there's another level of eval
	 * inside mksafefunc?
	 */
	count = perl_call_pv("PostgreSQL::InServer::mkfunc",
						 G_SCALAR | G_EVAL | G_KEEPERR);
	SPAGAIN;

	if (count == 1)
	{
		SV		   *sub_rv = (SV *) POPs;

		if (sub_rv && SvROK(sub_rv) && SvTYPE(SvRV(sub_rv)) == SVt_PVCV)
		{
			subref = newRV_inc(SvRV(sub_rv));
		}
	}

	PUTBACK;
	FREETMPS;
	LEAVE;

	if (SvTRUE(ERRSV))
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV)))));

	if (!subref)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("didn't get a CODE reference from compiling function \"%s\"",
						prodesc->proname)));

	prodesc->reference = subref;

	return;
}
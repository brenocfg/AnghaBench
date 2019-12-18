#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nargs; int /*<<< orphan*/  reference; int /*<<< orphan*/ * arg_out_func; int /*<<< orphan*/ * arg_arraytype; scalar_t__* arg_is_rowtype; } ;
typedef  TYPE_4__ plperl_proc_desc ;
struct TYPE_14__ {TYPE_2__* prodesc; } ;
struct TYPE_13__ {TYPE_3__* args; TYPE_1__* flinfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; scalar_t__ isnull; } ;
struct TYPE_10__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  lang_oid; } ;
struct TYPE_9__ {scalar_t__ fn_oid; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_5__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  EXTEND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FREETMPS ; 
 int G_EVAL ; 
 int G_SCALAR ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_sv_undef ; 
 int /*<<< orphan*/  POPs ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PUTBACK ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  SPAGAIN ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstr2sv (char*) ; 
 TYPE_8__* current_call_data ; 
 int /*<<< orphan*/  dSP ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_func_signature (scalar_t__,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  get_transform_fromsql (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newSVsv (int /*<<< orphan*/ ) ; 
 int perl_call_sv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/ * plperl_hash_from_datum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * plperl_ref_from_pg_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp ; 
 int /*<<< orphan*/  strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sv_2mortal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SV  *
plperl_call_perl_func(plperl_proc_desc *desc, FunctionCallInfo fcinfo)
{
	dTHX;
	dSP;
	SV		   *retval;
	int			i;
	int			count;
	Oid		   *argtypes = NULL;
	int			nargs = 0;

	ENTER;
	SAVETMPS;

	PUSHMARK(SP);
	EXTEND(sp, desc->nargs);

	/* Get signature for true functions; inline blocks have no args. */
	if (fcinfo->flinfo->fn_oid)
		get_func_signature(fcinfo->flinfo->fn_oid, &argtypes, &nargs);
	Assert(nargs == desc->nargs);

	for (i = 0; i < desc->nargs; i++)
	{
		if (fcinfo->args[i].isnull)
			PUSHs(&PL_sv_undef);
		else if (desc->arg_is_rowtype[i])
		{
			SV		   *sv = plperl_hash_from_datum(fcinfo->args[i].value);

			PUSHs(sv_2mortal(sv));
		}
		else
		{
			SV		   *sv;
			Oid			funcid;

			if (OidIsValid(desc->arg_arraytype[i]))
				sv = plperl_ref_from_pg_array(fcinfo->args[i].value, desc->arg_arraytype[i]);
			else if ((funcid = get_transform_fromsql(argtypes[i], current_call_data->prodesc->lang_oid, current_call_data->prodesc->trftypes)))
				sv = (SV *) DatumGetPointer(OidFunctionCall1(funcid, fcinfo->args[i].value));
			else
			{
				char	   *tmp;

				tmp = OutputFunctionCall(&(desc->arg_out_func[i]),
										 fcinfo->args[i].value);
				sv = cstr2sv(tmp);
				pfree(tmp);
			}

			PUSHs(sv_2mortal(sv));
		}
	}
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
				 errmsg("didn't get a return item from function")));
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

	PUTBACK;
	FREETMPS;
	LEAVE;

	return retval;
}
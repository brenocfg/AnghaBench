#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ TypeFuncClass ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_11__ {TYPE_1__* prodesc; } ;
struct TYPE_10__ {scalar_t__ tdtypeid; } ;
struct TYPE_9__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  lang_oid; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__ FunctionCallInfo ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InputFunctionCall (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_2__*) ; 
 scalar_t__ SVt_PVHV ; 
 int /*<<< orphan*/  SvOK (int /*<<< orphan*/ *) ; 
 scalar_t__ SvROK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SvRV (int /*<<< orphan*/ *) ; 
 scalar_t__ SvTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 scalar_t__ TYPEFUNC_COMPOSITE_DOMAIN ; 
 scalar_t__ TYPEFUNC_OTHER ; 
 scalar_t__ VOIDOID ; 
 int /*<<< orphan*/  _sv_to_datum_finfo (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 TYPE_6__* current_call_data ; 
 int /*<<< orphan*/  domain_check (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_call_result_type (scalar_t__,scalar_t__*,TYPE_2__**) ; 
 int /*<<< orphan*/ * get_perl_array_ref (int /*<<< orphan*/ *) ; 
 scalar_t__ get_transform_tosql (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* lookup_rowtype_tupdesc_domain (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  plperl_array_to_datum (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plperl_hash_to_datum (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* sv2cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_is_rowtype (scalar_t__) ; 

__attribute__((used)) static Datum
plperl_sv_to_datum(SV *sv, Oid typid, int32 typmod,
				   FunctionCallInfo fcinfo,
				   FmgrInfo *finfo, Oid typioparam,
				   bool *isnull)
{
	FmgrInfo	tmp;
	Oid			funcid;

	/* we might recurse */
	check_stack_depth();

	*isnull = false;

	/*
	 * Return NULL if result is undef, or if we're in a function returning
	 * VOID.  In the latter case, we should pay no attention to the last Perl
	 * statement's result, and this is a convenient means to ensure that.
	 */
	if (!sv || !SvOK(sv) || typid == VOIDOID)
	{
		/* look up type info if they did not pass it */
		if (!finfo)
		{
			_sv_to_datum_finfo(typid, &tmp, &typioparam);
			finfo = &tmp;
		}
		*isnull = true;
		/* must call typinput in case it wants to reject NULL */
		return InputFunctionCall(finfo, NULL, typioparam, typmod);
	}
	else if ((funcid = get_transform_tosql(typid, current_call_data->prodesc->lang_oid, current_call_data->prodesc->trftypes)))
		return OidFunctionCall1(funcid, PointerGetDatum(sv));
	else if (SvROK(sv))
	{
		/* handle references */
		SV		   *sav = get_perl_array_ref(sv);

		if (sav)
		{
			/* handle an arrayref */
			return plperl_array_to_datum(sav, typid, typmod);
		}
		else if (SvTYPE(SvRV(sv)) == SVt_PVHV)
		{
			/* handle a hashref */
			Datum		ret;
			TupleDesc	td;
			bool		isdomain;

			if (!type_is_rowtype(typid))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("cannot convert Perl hash to non-composite type %s",
								format_type_be(typid))));

			td = lookup_rowtype_tupdesc_domain(typid, typmod, true);
			if (td != NULL)
			{
				/* Did we look through a domain? */
				isdomain = (typid != td->tdtypeid);
			}
			else
			{
				/* Must be RECORD, try to resolve based on call info */
				TypeFuncClass funcclass;

				if (fcinfo)
					funcclass = get_call_result_type(fcinfo, &typid, &td);
				else
					funcclass = TYPEFUNC_OTHER;
				if (funcclass != TYPEFUNC_COMPOSITE &&
					funcclass != TYPEFUNC_COMPOSITE_DOMAIN)
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("function returning record called in context "
									"that cannot accept type record")));
				Assert(td);
				isdomain = (funcclass == TYPEFUNC_COMPOSITE_DOMAIN);
			}

			ret = plperl_hash_to_datum(sv, td);

			if (isdomain)
				domain_check(ret, false, typid, NULL, NULL);

			/* Release on the result of get_call_result_type is harmless */
			ReleaseTupleDesc(td);

			return ret;
		}

		/*
		 * If it's a reference to something else, such as a scalar, just
		 * recursively look through the reference.
		 */
		return plperl_sv_to_datum(SvRV(sv), typid, typmod,
								  fcinfo, finfo, typioparam,
								  isnull);
	}
	else
	{
		/* handle a string/number */
		Datum		ret;
		char	   *str = sv2cstr(sv);

		/* did not pass in any typeinfo? look it up */
		if (!finfo)
		{
			_sv_to_datum_finfo(typid, &tmp, &typioparam);
			finfo = &tmp;
		}

		ret = InputFunctionCall(finfo, str, typioparam, typmod);
		pfree(str);

		return ret;
	}
}
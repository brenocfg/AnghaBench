#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  result_typioparam; int /*<<< orphan*/  result_in_func; scalar_t__ result_oid; scalar_t__ fn_retistuple; int /*<<< orphan*/  fn_retisset; } ;
typedef  TYPE_2__ plperl_proc_desc ;
typedef  scalar_t__ TypeFuncClass ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_16__ {scalar_t__ tmp_cxt; scalar_t__ ret_tdesc; scalar_t__ tuple_store; int /*<<< orphan*/  cdomain_info; int /*<<< orphan*/  cdomain_oid; TYPE_5__* fcinfo; TYPE_2__* prodesc; } ;
struct TYPE_15__ {scalar_t__ resultinfo; } ;
struct TYPE_14__ {int allowedModes; TYPE_1__* econtext; TYPE_3__* expectedDesc; } ;
struct TYPE_13__ {int natts; } ;
struct TYPE_11__ {scalar_t__ ecxt_per_query_memory; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_4__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HV ;
typedef  TYPE_5__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 scalar_t__ AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CreateTupleDescCopy (TYPE_3__*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (scalar_t__) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int SFRM_Materialize_Random ; 
 scalar_t__ SVt_PVHV ; 
 scalar_t__ SvOK (int /*<<< orphan*/ *) ; 
 scalar_t__ SvROK (int /*<<< orphan*/ *) ; 
 scalar_t__ SvRV (int /*<<< orphan*/ *) ; 
 scalar_t__ SvTYPE (scalar_t__) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 scalar_t__ TYPEFUNC_COMPOSITE_DOMAIN ; 
 TYPE_9__* current_call_data ; 
 int /*<<< orphan*/  domain_check (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_call_result_type (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  plperl_build_tuple_result (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  plperl_sv_to_datum (int /*<<< orphan*/ *,scalar_t__,int,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttuple (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_putvalues (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
plperl_return_next_internal(SV *sv)
{
	plperl_proc_desc *prodesc;
	FunctionCallInfo fcinfo;
	ReturnSetInfo *rsi;
	MemoryContext old_cxt;

	if (!sv)
		return;

	prodesc = current_call_data->prodesc;
	fcinfo = current_call_data->fcinfo;
	rsi = (ReturnSetInfo *) fcinfo->resultinfo;

	if (!prodesc->fn_retisset)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("cannot use return_next in a non-SETOF function")));

	if (!current_call_data->ret_tdesc)
	{
		TupleDesc	tupdesc;

		Assert(!current_call_data->tuple_store);

		/*
		 * This is the first call to return_next in the current PL/Perl
		 * function call, so identify the output tuple type and create a
		 * tuplestore to hold the result rows.
		 */
		if (prodesc->fn_retistuple)
		{
			TypeFuncClass funcclass;
			Oid			typid;

			funcclass = get_call_result_type(fcinfo, &typid, &tupdesc);
			if (funcclass != TYPEFUNC_COMPOSITE &&
				funcclass != TYPEFUNC_COMPOSITE_DOMAIN)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("function returning record called in context "
								"that cannot accept type record")));
			/* if domain-over-composite, remember the domain's type OID */
			if (funcclass == TYPEFUNC_COMPOSITE_DOMAIN)
				current_call_data->cdomain_oid = typid;
		}
		else
		{
			tupdesc = rsi->expectedDesc;
			/* Protect assumption below that we return exactly one column */
			if (tupdesc == NULL || tupdesc->natts != 1)
				elog(ERROR, "expected single-column result descriptor for non-composite SETOF result");
		}

		/*
		 * Make sure the tuple_store and ret_tdesc are sufficiently
		 * long-lived.
		 */
		old_cxt = MemoryContextSwitchTo(rsi->econtext->ecxt_per_query_memory);

		current_call_data->ret_tdesc = CreateTupleDescCopy(tupdesc);
		current_call_data->tuple_store =
			tuplestore_begin_heap(rsi->allowedModes & SFRM_Materialize_Random,
								  false, work_mem);

		MemoryContextSwitchTo(old_cxt);
	}

	/*
	 * Producing the tuple we want to return requires making plenty of
	 * palloc() allocations that are not cleaned up. Since this function can
	 * be called many times before the current memory context is reset, we
	 * need to do those allocations in a temporary context.
	 */
	if (!current_call_data->tmp_cxt)
	{
		current_call_data->tmp_cxt =
			AllocSetContextCreate(CurrentMemoryContext,
								  "PL/Perl return_next temporary cxt",
								  ALLOCSET_DEFAULT_SIZES);
	}

	old_cxt = MemoryContextSwitchTo(current_call_data->tmp_cxt);

	if (prodesc->fn_retistuple)
	{
		HeapTuple	tuple;

		if (!(SvOK(sv) && SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PVHV))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("SETOF-composite-returning PL/Perl function "
							"must call return_next with reference to hash")));

		tuple = plperl_build_tuple_result((HV *) SvRV(sv),
										  current_call_data->ret_tdesc);

		if (OidIsValid(current_call_data->cdomain_oid))
			domain_check(HeapTupleGetDatum(tuple), false,
						 current_call_data->cdomain_oid,
						 &current_call_data->cdomain_info,
						 rsi->econtext->ecxt_per_query_memory);

		tuplestore_puttuple(current_call_data->tuple_store, tuple);
	}
	else if (prodesc->result_oid)
	{
		Datum		ret[1];
		bool		isNull[1];

		ret[0] = plperl_sv_to_datum(sv,
									prodesc->result_oid,
									-1,
									fcinfo,
									&prodesc->result_in_func,
									prodesc->result_typioparam,
									&isNull[0]);

		tuplestore_putvalues(current_call_data->tuple_store,
							 current_call_data->ret_tdesc,
							 ret, isNull);
	}

	MemoryContextSwitchTo(old_cxt);
	MemoryContextReset(current_call_data->tmp_cxt);
}
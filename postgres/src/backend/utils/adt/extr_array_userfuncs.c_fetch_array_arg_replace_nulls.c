#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* fn_extra; int /*<<< orphan*/  fn_mcxt; } ;
struct TYPE_9__ {int /*<<< orphan*/  element_type; } ;
struct TYPE_8__ {TYPE_3__* flinfo; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  ExpandedArrayHeader ;
typedef  TYPE_2__ ArrayMetaState ;

/* Variables and functions */
 int /*<<< orphan*/  AggCheckCallContext (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_ARGISNULL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_EXPANDED_ARRAYX (int,TYPE_2__*) ; 
 int /*<<< orphan*/ * construct_empty_expanded_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fn_expr_argtype (TYPE_3__*,int) ; 

__attribute__((used)) static ExpandedArrayHeader *
fetch_array_arg_replace_nulls(FunctionCallInfo fcinfo, int argno)
{
	ExpandedArrayHeader *eah;
	Oid			element_type;
	ArrayMetaState *my_extra;
	MemoryContext resultcxt;

	/* If first time through, create datatype cache struct */
	my_extra = (ArrayMetaState *) fcinfo->flinfo->fn_extra;
	if (my_extra == NULL)
	{
		my_extra = (ArrayMetaState *)
			MemoryContextAlloc(fcinfo->flinfo->fn_mcxt,
							   sizeof(ArrayMetaState));
		my_extra->element_type = InvalidOid;
		fcinfo->flinfo->fn_extra = my_extra;
	}

	/* Figure out which context we want the result in */
	if (!AggCheckCallContext(fcinfo, &resultcxt))
		resultcxt = CurrentMemoryContext;

	/* Now collect the array value */
	if (!PG_ARGISNULL(argno))
	{
		MemoryContext oldcxt = MemoryContextSwitchTo(resultcxt);

		eah = PG_GETARG_EXPANDED_ARRAYX(argno, my_extra);
		MemoryContextSwitchTo(oldcxt);
	}
	else
	{
		/* We have to look up the array type and element type */
		Oid			arr_typeid = get_fn_expr_argtype(fcinfo->flinfo, argno);

		if (!OidIsValid(arr_typeid))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("could not determine input data type")));
		element_type = get_element_type(arr_typeid);
		if (!OidIsValid(element_type))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("input data type is not an array")));

		eah = construct_empty_expanded_array(element_type,
											 resultcxt,
											 my_extra);
	}

	return eah;
}
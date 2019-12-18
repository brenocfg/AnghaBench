#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_12__ {scalar_t__ fn_extra; } ;
struct TYPE_11__ {TYPE_4__* flinfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 char const* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PG_ARGISNULL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_ARRAYTYPE_P (int) ; 
 int /*<<< orphan*/  PG_GETARG_DATUM (int) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * array_to_text_internal (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_concat_foutcache (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * cstring_to_text_with_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_base_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fn_expr_argtype (TYPE_4__*,int) ; 
 scalar_t__ get_fn_expr_variadic (TYPE_4__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static text *
concat_internal(const char *sepstr, int argidx,
				FunctionCallInfo fcinfo)
{
	text	   *result;
	StringInfoData str;
	FmgrInfo   *foutcache;
	bool		first_arg = true;
	int			i;

	/*
	 * concat(VARIADIC some-array) is essentially equivalent to
	 * array_to_text(), ie concat the array elements with the given separator.
	 * So we just pass the case off to that code.
	 */
	if (get_fn_expr_variadic(fcinfo->flinfo))
	{
		ArrayType  *arr;

		/* Should have just the one argument */
		Assert(argidx == PG_NARGS() - 1);

		/* concat(VARIADIC NULL) is defined as NULL */
		if (PG_ARGISNULL(argidx))
			return NULL;

		/*
		 * Non-null argument had better be an array.  We assume that any call
		 * context that could let get_fn_expr_variadic return true will have
		 * checked that a VARIADIC-labeled parameter actually is an array.  So
		 * it should be okay to just Assert that it's an array rather than
		 * doing a full-fledged error check.
		 */
		Assert(OidIsValid(get_base_element_type(get_fn_expr_argtype(fcinfo->flinfo, argidx))));

		/* OK, safe to fetch the array value */
		arr = PG_GETARG_ARRAYTYPE_P(argidx);

		/*
		 * And serialize the array.  We tell array_to_text to ignore null
		 * elements, which matches the behavior of the loop below.
		 */
		return array_to_text_internal(fcinfo, arr, sepstr, NULL);
	}

	/* Normal case without explicit VARIADIC marker */
	initStringInfo(&str);

	/* Get output function info, building it if first time through */
	foutcache = (FmgrInfo *) fcinfo->flinfo->fn_extra;
	if (foutcache == NULL)
		foutcache = build_concat_foutcache(fcinfo, argidx);

	for (i = argidx; i < PG_NARGS(); i++)
	{
		if (!PG_ARGISNULL(i))
		{
			Datum		value = PG_GETARG_DATUM(i);

			/* add separator if appropriate */
			if (first_arg)
				first_arg = false;
			else
				appendStringInfoString(&str, sepstr);

			/* call the appropriate type output function, append the result */
			appendStringInfoString(&str,
								   OutputFunctionCall(&foutcache[i], value));
		}
	}

	result = cstring_to_text_with_len(str.data, str.len);
	pfree(str.data);

	return result;
}
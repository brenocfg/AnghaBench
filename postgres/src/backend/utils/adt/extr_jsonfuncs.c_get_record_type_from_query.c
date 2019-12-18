#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  base_typmod; int /*<<< orphan*/  base_typid; int /*<<< orphan*/  tupdesc; } ;
struct TYPE_11__ {TYPE_1__ composite; } ;
struct TYPE_12__ {TYPE_2__ io; } ;
struct TYPE_14__ {TYPE_3__ c; int /*<<< orphan*/  fn_mcxt; int /*<<< orphan*/  argtype; } ;
struct TYPE_13__ {int /*<<< orphan*/  tdtypmod; int /*<<< orphan*/  tdtypeid; } ;
typedef  TYPE_5__ PopulateRecordCache ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (TYPE_4__*) ; 
 int /*<<< orphan*/  CreateTupleDescCopy (TYPE_4__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__**) ; 

__attribute__((used)) static void
get_record_type_from_query(FunctionCallInfo fcinfo,
						   const char *funcname,
						   PopulateRecordCache *cache)
{
	TupleDesc	tupdesc;
	MemoryContext old_cxt;

	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
		/* translator: %s is a function name, eg json_to_record */
				 errmsg("could not determine row type for result of %s",
						funcname),
				 errhint("Provide a non-null record argument, "
						 "or call the function in the FROM clause "
						 "using a column definition list.")));

	Assert(tupdesc);
	cache->argtype = tupdesc->tdtypeid;

	/* If we go through this more than once, avoid memory leak */
	if (cache->c.io.composite.tupdesc)
		FreeTupleDesc(cache->c.io.composite.tupdesc);

	/* Save identified tupdesc */
	old_cxt = MemoryContextSwitchTo(cache->fn_mcxt);
	cache->c.io.composite.tupdesc = CreateTupleDescCopy(tupdesc);
	cache->c.io.composite.base_typid = tupdesc->tdtypeid;
	cache->c.io.composite.base_typmod = tupdesc->tdtypmod;
	MemoryContextSwitchTo(old_cxt);
}
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
struct TYPE_3__ {scalar_t__ gt_opr; scalar_t__ lt_opr; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int TYPECACHE_GT_OPR ; 
 int TYPECACHE_LT_OPR ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 char* get_collation_name (scalar_t__) ; 
 int /*<<< orphan*/  get_equality_op_for_ordering_op (scalar_t__,int*) ; 
 char* get_opname (scalar_t__) ; 
 scalar_t__ get_typcollation (scalar_t__) ; 
 TYPE_1__* lookup_type_cache (scalar_t__,int) ; 
 char* quote_identifier (char*) ; 

__attribute__((used)) static void
show_sortorder_options(StringInfo buf, Node *sortexpr,
					   Oid sortOperator, Oid collation, bool nullsFirst)
{
	Oid			sortcoltype = exprType(sortexpr);
	bool		reverse = false;
	TypeCacheEntry *typentry;

	typentry = lookup_type_cache(sortcoltype,
								 TYPECACHE_LT_OPR | TYPECACHE_GT_OPR);

	/*
	 * Print COLLATE if it's not default for the column's type.  There are
	 * some cases where this is redundant, eg if expression is a column whose
	 * declared collation is that collation, but it's hard to distinguish that
	 * here (and arguably, printing COLLATE explicitly is a good idea anyway
	 * in such cases).
	 */
	if (OidIsValid(collation) && collation != get_typcollation(sortcoltype))
	{
		char	   *collname = get_collation_name(collation);

		if (collname == NULL)
			elog(ERROR, "cache lookup failed for collation %u", collation);
		appendStringInfo(buf, " COLLATE %s", quote_identifier(collname));
	}

	/* Print direction if not ASC, or USING if non-default sort operator */
	if (sortOperator == typentry->gt_opr)
	{
		appendStringInfoString(buf, " DESC");
		reverse = true;
	}
	else if (sortOperator != typentry->lt_opr)
	{
		char	   *opname = get_opname(sortOperator);

		if (opname == NULL)
			elog(ERROR, "cache lookup failed for operator %u", sortOperator);
		appendStringInfo(buf, " USING %s", opname);
		/* Determine whether operator would be considered ASC or DESC */
		(void) get_equality_op_for_ordering_op(sortOperator, &reverse);
	}

	/* Add NULLS FIRST/LAST only if it wouldn't be default */
	if (nullsFirst && !reverse)
	{
		appendStringInfoString(buf, " NULLS FIRST");
	}
	else if (!nullsFirst && reverse)
	{
		appendStringInfoString(buf, " NULLS LAST");
	}
}
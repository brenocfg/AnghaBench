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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * bms_make_singleton (scalar_t__) ; 
 int /*<<< orphan*/  deparseTargetList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pull_varattnos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
deparseReturningList(StringInfo buf, RangeTblEntry *rte,
					 Index rtindex, Relation rel,
					 bool trig_after_row,
					 List *withCheckOptionList,
					 List *returningList,
					 List **retrieved_attrs)
{
	Bitmapset  *attrs_used = NULL;

	if (trig_after_row)
	{
		/* whole-row reference acquires all non-system columns */
		attrs_used =
			bms_make_singleton(0 - FirstLowInvalidHeapAttributeNumber);
	}

	if (withCheckOptionList != NIL)
	{
		/*
		 * We need the attrs, non-system and system, mentioned in the local
		 * query's WITH CHECK OPTION list.
		 *
		 * Note: we do this to ensure that WCO constraints will be evaluated
		 * on the data actually inserted/updated on the remote side, which
		 * might differ from the data supplied by the core code, for example
		 * as a result of remote triggers.
		 */
		pull_varattnos((Node *) withCheckOptionList, rtindex,
					   &attrs_used);
	}

	if (returningList != NIL)
	{
		/*
		 * We need the attrs, non-system and system, mentioned in the local
		 * query's RETURNING list.
		 */
		pull_varattnos((Node *) returningList, rtindex,
					   &attrs_used);
	}

	if (attrs_used != NULL)
		deparseTargetList(buf, rte, rtindex, rel, true, attrs_used, false,
						  retrieved_attrs);
	else
		*retrieved_attrs = NIL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  depends_on; TYPE_1__* cte; } ;
struct TYPE_4__ {int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  TYPE_2__ CteItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  bms_del_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TopologicalSort(ParseState *pstate, CteItem *items, int numitems)
{
	int			i,
				j;

	/* for each position in sequence ... */
	for (i = 0; i < numitems; i++)
	{
		/* ... scan the remaining items to find one that has no dependencies */
		for (j = i; j < numitems; j++)
		{
			if (bms_is_empty(items[j].depends_on))
				break;
		}

		/* if we didn't find one, the dependency graph has a cycle */
		if (j >= numitems)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("mutual recursion between WITH items is not implemented"),
					 parser_errposition(pstate, items[i].cte->location)));

		/*
		 * Found one.  Move it to front and remove it from every other item's
		 * dependencies.
		 */
		if (i != j)
		{
			CteItem		tmp;

			tmp = items[i];
			items[i] = items[j];
			items[j] = tmp;
		}

		/*
		 * Items up through i are known to have no dependencies left, so we
		 * can skip them in this loop.
		 */
		for (j = i + 1; j < numitems; j++)
		{
			items[j].depends_on = bms_del_member(items[j].depends_on,
												 items[i].id);
		}
	}
}
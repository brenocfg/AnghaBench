#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplesortstate ;
struct TYPE_13__ {long spaceUsed; int /*<<< orphan*/  spaceType; int /*<<< orphan*/  sortMethod; } ;
typedef  TYPE_2__ TuplesortInstrumentation ;
struct TYPE_15__ {scalar_t__ format; int indent; int /*<<< orphan*/  str; int /*<<< orphan*/  analyze; } ;
struct TYPE_14__ {TYPE_1__* shared_info; int /*<<< orphan*/ * tuplesortstate; scalar_t__ sort_Done; } ;
struct TYPE_12__ {int num_workers; TYPE_2__* sinstrument; } ;
typedef  TYPE_3__ SortState ;
typedef  TYPE_4__ ExplainState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExplainCloseGroup (char*,char*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  ExplainOpenGroup (char*,char*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  ExplainPropertyInteger (char*,char*,long,TYPE_4__*) ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,char const*,TYPE_4__*) ; 
 int /*<<< orphan*/  SORT_TYPE_STILL_IN_PROGRESS ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tuplesort_get_stats (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* tuplesort_method_name (int /*<<< orphan*/ ) ; 
 char* tuplesort_space_type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_sort_info(SortState *sortstate, ExplainState *es)
{
	if (!es->analyze)
		return;

	if (sortstate->sort_Done && sortstate->tuplesortstate != NULL)
	{
		Tuplesortstate *state = (Tuplesortstate *) sortstate->tuplesortstate;
		TuplesortInstrumentation stats;
		const char *sortMethod;
		const char *spaceType;
		long		spaceUsed;

		tuplesort_get_stats(state, &stats);
		sortMethod = tuplesort_method_name(stats.sortMethod);
		spaceType = tuplesort_space_type_name(stats.spaceType);
		spaceUsed = stats.spaceUsed;

		if (es->format == EXPLAIN_FORMAT_TEXT)
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfo(es->str, "Sort Method: %s  %s: %ldkB\n",
							 sortMethod, spaceType, spaceUsed);
		}
		else
		{
			ExplainPropertyText("Sort Method", sortMethod, es);
			ExplainPropertyInteger("Sort Space Used", "kB", spaceUsed, es);
			ExplainPropertyText("Sort Space Type", spaceType, es);
		}
	}

	if (sortstate->shared_info != NULL)
	{
		int			n;
		bool		opened_group = false;

		for (n = 0; n < sortstate->shared_info->num_workers; n++)
		{
			TuplesortInstrumentation *sinstrument;
			const char *sortMethod;
			const char *spaceType;
			long		spaceUsed;

			sinstrument = &sortstate->shared_info->sinstrument[n];
			if (sinstrument->sortMethod == SORT_TYPE_STILL_IN_PROGRESS)
				continue;		/* ignore any unfilled slots */
			sortMethod = tuplesort_method_name(sinstrument->sortMethod);
			spaceType = tuplesort_space_type_name(sinstrument->spaceType);
			spaceUsed = sinstrument->spaceUsed;

			if (es->format == EXPLAIN_FORMAT_TEXT)
			{
				appendStringInfoSpaces(es->str, es->indent * 2);
				appendStringInfo(es->str,
								 "Worker %d:  Sort Method: %s  %s: %ldkB\n",
								 n, sortMethod, spaceType, spaceUsed);
			}
			else
			{
				if (!opened_group)
				{
					ExplainOpenGroup("Workers", "Workers", false, es);
					opened_group = true;
				}
				ExplainOpenGroup("Worker", NULL, true, es);
				ExplainPropertyInteger("Worker Number", NULL, n, es);
				ExplainPropertyText("Sort Method", sortMethod, es);
				ExplainPropertyInteger("Sort Space Used", "kB", spaceUsed, es);
				ExplainPropertyText("Sort Space Type", spaceType, es);
				ExplainCloseGroup("Worker", NULL, true, es);
			}
		}
		if (opened_group)
			ExplainCloseGroup("Workers", "Workers", false, es);
	}
}
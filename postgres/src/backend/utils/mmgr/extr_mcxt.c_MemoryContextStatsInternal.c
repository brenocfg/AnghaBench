#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  local_totals ;
struct TYPE_12__ {struct TYPE_12__* nextchild; struct TYPE_12__* firstchild; TYPE_1__* methods; } ;
struct TYPE_11__ {scalar_t__ freespace; scalar_t__ totalspace; scalar_t__ freechunks; scalar_t__ nblocks; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* stats ) (TYPE_3__*,int /*<<< orphan*/ *,void*,TYPE_2__*) ;} ;
typedef  TYPE_2__ MemoryContextCounters ;
typedef  TYPE_3__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/ * MemoryContextStatsPrint ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,void*,TYPE_2__*) ; 

__attribute__((used)) static void
MemoryContextStatsInternal(MemoryContext context, int level,
						   bool print, int max_children,
						   MemoryContextCounters *totals)
{
	MemoryContextCounters local_totals;
	MemoryContext child;
	int			ichild;

	AssertArg(MemoryContextIsValid(context));

	/* Examine the context itself */
	context->methods->stats(context,
							print ? MemoryContextStatsPrint : NULL,
							(void *) &level,
							totals);

	/*
	 * Examine children.  If there are more than max_children of them, we do
	 * not print the rest explicitly, but just summarize them.
	 */
	memset(&local_totals, 0, sizeof(local_totals));

	for (child = context->firstchild, ichild = 0;
		 child != NULL;
		 child = child->nextchild, ichild++)
	{
		if (ichild < max_children)
			MemoryContextStatsInternal(child, level + 1,
									   print, max_children,
									   totals);
		else
			MemoryContextStatsInternal(child, level + 1,
									   false, max_children,
									   &local_totals);
	}

	/* Deal with excess children */
	if (ichild > max_children)
	{
		if (print)
		{
			int			i;

			for (i = 0; i <= level; i++)
				fprintf(stderr, "  ");
			fprintf(stderr,
					"%d more child contexts containing %zu total in %zd blocks; %zu free (%zd chunks); %zu used\n",
					ichild - max_children,
					local_totals.totalspace,
					local_totals.nblocks,
					local_totals.freespace,
					local_totals.freechunks,
					local_totals.totalspace - local_totals.freespace);
		}

		if (totals)
		{
			totals->nblocks += local_totals.nblocks;
			totals->freechunks += local_totals.freechunks;
			totals->totalspace += local_totals.totalspace;
			totals->freespace += local_totals.freespace;
		}
	}
}
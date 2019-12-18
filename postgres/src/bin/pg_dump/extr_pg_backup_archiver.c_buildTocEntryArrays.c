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
struct TYPE_4__ {int dumpId; scalar_t__ nDeps; int* dependencies; int /*<<< orphan*/  desc; struct TYPE_4__* next; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_5__ {int maxDumpId; int* tableDataId; TYPE_1__** tocsByDumpId; TYPE_1__* toc; } ;
typedef  int DumpId ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ pg_malloc0 (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
buildTocEntryArrays(ArchiveHandle *AH)
{
	DumpId		maxDumpId = AH->maxDumpId;
	TocEntry   *te;

	AH->tocsByDumpId = (TocEntry **) pg_malloc0((maxDumpId + 1) * sizeof(TocEntry *));
	AH->tableDataId = (DumpId *) pg_malloc0((maxDumpId + 1) * sizeof(DumpId));

	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		/* this check is purely paranoia, maxDumpId should be correct */
		if (te->dumpId <= 0 || te->dumpId > maxDumpId)
			fatal("bad dumpId");

		/* tocsByDumpId indexes all TOCs by their dump ID */
		AH->tocsByDumpId[te->dumpId] = te;

		/*
		 * tableDataId provides the TABLE DATA item's dump ID for each TABLE
		 * TOC entry that has a DATA item.  We compute this by reversing the
		 * TABLE DATA item's dependency, knowing that a TABLE DATA item has
		 * just one dependency and it is the TABLE item.
		 */
		if (strcmp(te->desc, "TABLE DATA") == 0 && te->nDeps > 0)
		{
			DumpId		tableId = te->dependencies[0];

			/*
			 * The TABLE item might not have been in the archive, if this was
			 * a data-only dump; but its dump ID should be less than its data
			 * item's dump ID, so there should be a place for it in the array.
			 */
			if (tableId <= 0 || tableId > maxDumpId)
				fatal("bad table dumpId for TABLE DATA item");

			AH->tableDataId[tableId] = te->dumpId;
		}
	}
}
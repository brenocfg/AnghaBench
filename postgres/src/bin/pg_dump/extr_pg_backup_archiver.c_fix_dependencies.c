#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int depCount; int nDeps; size_t* revDeps; int nRevDeps; size_t* dependencies; size_t dumpId; scalar_t__ nLockDeps; int /*<<< orphan*/ * lockDeps; struct TYPE_7__* next; int /*<<< orphan*/  desc; int /*<<< orphan*/ * pending_next; int /*<<< orphan*/ * pending_prev; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_8__ {scalar_t__ version; size_t maxDumpId; TYPE_1__* toc; TYPE_1__** tocsByDumpId; } ;
typedef  size_t DumpId ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ K_VERS_1_11 ; 
 int /*<<< orphan*/  identify_locking_dependencies (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  repoint_table_dependencies (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fix_dependencies(ArchiveHandle *AH)
{
	TocEntry   *te;
	int			i;

	/*
	 * Initialize the depCount/revDeps/nRevDeps fields, and make sure the TOC
	 * items are marked as not being in any parallel-processing list.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		te->depCount = te->nDeps;
		te->revDeps = NULL;
		te->nRevDeps = 0;
		te->pending_prev = NULL;
		te->pending_next = NULL;
	}

	/*
	 * POST_DATA items that are shown as depending on a table need to be
	 * re-pointed to depend on that table's data, instead.  This ensures they
	 * won't get scheduled until the data has been loaded.
	 */
	repoint_table_dependencies(AH);

	/*
	 * Pre-8.4 versions of pg_dump neglected to set up a dependency from BLOB
	 * COMMENTS to BLOBS.  Cope.  (We assume there's only one BLOBS and only
	 * one BLOB COMMENTS in such files.)
	 */
	if (AH->version < K_VERS_1_11)
	{
		for (te = AH->toc->next; te != AH->toc; te = te->next)
		{
			if (strcmp(te->desc, "BLOB COMMENTS") == 0 && te->nDeps == 0)
			{
				TocEntry   *te2;

				for (te2 = AH->toc->next; te2 != AH->toc; te2 = te2->next)
				{
					if (strcmp(te2->desc, "BLOBS") == 0)
					{
						te->dependencies = (DumpId *) pg_malloc(sizeof(DumpId));
						te->dependencies[0] = te2->dumpId;
						te->nDeps++;
						te->depCount++;
						break;
					}
				}
				break;
			}
		}
	}

	/*
	 * At this point we start to build the revDeps reverse-dependency arrays,
	 * so all changes of dependencies must be complete.
	 */

	/*
	 * Count the incoming dependencies for each item.  Also, it is possible
	 * that the dependencies list items that are not in the archive at all
	 * (that should not happen in 9.2 and later, but is highly likely in older
	 * archives).  Subtract such items from the depCounts.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		for (i = 0; i < te->nDeps; i++)
		{
			DumpId		depid = te->dependencies[i];

			if (depid <= AH->maxDumpId && AH->tocsByDumpId[depid] != NULL)
				AH->tocsByDumpId[depid]->nRevDeps++;
			else
				te->depCount--;
		}
	}

	/*
	 * Allocate space for revDeps[] arrays, and reset nRevDeps so we can use
	 * it as a counter below.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		if (te->nRevDeps > 0)
			te->revDeps = (DumpId *) pg_malloc(te->nRevDeps * sizeof(DumpId));
		te->nRevDeps = 0;
	}

	/*
	 * Build the revDeps[] arrays of incoming-dependency dumpIds.  This had
	 * better agree with the loops above.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		for (i = 0; i < te->nDeps; i++)
		{
			DumpId		depid = te->dependencies[i];

			if (depid <= AH->maxDumpId && AH->tocsByDumpId[depid] != NULL)
			{
				TocEntry   *otherte = AH->tocsByDumpId[depid];

				otherte->revDeps[otherte->nRevDeps++] = te->dumpId;
			}
		}
	}

	/*
	 * Lastly, work out the locking dependencies.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		te->lockDeps = NULL;
		te->nLockDeps = 0;
		identify_locking_dependencies(AH, te);
	}
}
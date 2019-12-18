#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nRevDeps; size_t* revDeps; scalar_t__ depCount; int /*<<< orphan*/ * pending_prev; int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_9__ {scalar_t__ restorePass; TYPE_1__** tocsByDumpId; } ;
typedef  int /*<<< orphan*/  ParallelReadyList ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ _tocEntryRestorePass (TYPE_1__*) ; 
 int /*<<< orphan*/  pending_list_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ready_list_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
reduce_dependencies(ArchiveHandle *AH, TocEntry *te,
					ParallelReadyList *ready_list)
{
	int			i;

	pg_log_debug("reducing dependencies for %d", te->dumpId);

	for (i = 0; i < te->nRevDeps; i++)
	{
		TocEntry   *otherte = AH->tocsByDumpId[te->revDeps[i]];

		Assert(otherte->depCount > 0);
		otherte->depCount--;

		/*
		 * It's ready if it has no remaining dependencies, and it belongs in
		 * the current restore pass, and it is currently a member of the
		 * pending list (that check is needed to prevent double restore in
		 * some cases where a list-file forces out-of-order restoring).
		 * However, if ready_list == NULL then caller doesn't want any list
		 * memberships changed.
		 */
		if (otherte->depCount == 0 &&
			_tocEntryRestorePass(otherte) == AH->restorePass &&
			otherte->pending_prev != NULL &&
			ready_list != NULL)
		{
			/* Remove it from pending list ... */
			pending_list_remove(otherte);
			/* ... and add to ready_list */
			ready_list_insert(ready_list, otherte);
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ section; int /*<<< orphan*/  tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  dumpId; struct TYPE_13__* next; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_14__ {int /*<<< orphan*/ * currTableAm; int /*<<< orphan*/ * currTablespace; int /*<<< orphan*/ * currSchema; int /*<<< orphan*/ * currUser; int /*<<< orphan*/  public; TYPE_1__* toc; scalar_t__ restorePass; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  DisconnectDatabase (int /*<<< orphan*/ *) ; 
 scalar_t__ RESTORE_PASS_MAIN ; 
 scalar_t__ SECTION_DATA ; 
 scalar_t__ SECTION_POST_DATA ; 
 scalar_t__ SECTION_PRE_DATA ; 
 scalar_t__ _tocEntryRestorePass (TYPE_1__*) ; 
 int /*<<< orphan*/  fix_dependencies (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_list_append (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_debug (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reduce_dependencies (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_toc_entry (TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
restore_toc_entries_prefork(ArchiveHandle *AH, TocEntry *pending_list)
{
	bool		skipped_some;
	TocEntry   *next_work_item;

	pg_log_debug("entering restore_toc_entries_prefork");

	/* Adjust dependency information */
	fix_dependencies(AH);

	/*
	 * Do all the early stuff in a single connection in the parent. There's no
	 * great point in running it in parallel, in fact it will actually run
	 * faster in a single connection because we avoid all the connection and
	 * setup overhead.  Also, pre-9.2 pg_dump versions were not very good
	 * about showing all the dependencies of SECTION_PRE_DATA items, so we do
	 * not risk trying to process them out-of-order.
	 *
	 * Stuff that we can't do immediately gets added to the pending_list.
	 * Note: we don't yet filter out entries that aren't going to be restored.
	 * They might participate in dependency chains connecting entries that
	 * should be restored, so we treat them as live until we actually process
	 * them.
	 *
	 * Note: as of 9.2, it should be guaranteed that all PRE_DATA items appear
	 * before DATA items, and all DATA items before POST_DATA items.  That is
	 * not certain to be true in older archives, though, and in any case use
	 * of a list file would destroy that ordering (cf. SortTocFromFile).  So
	 * this loop cannot assume that it holds.
	 */
	AH->restorePass = RESTORE_PASS_MAIN;
	skipped_some = false;
	for (next_work_item = AH->toc->next; next_work_item != AH->toc; next_work_item = next_work_item->next)
	{
		bool		do_now = true;

		if (next_work_item->section != SECTION_PRE_DATA)
		{
			/* DATA and POST_DATA items are just ignored for now */
			if (next_work_item->section == SECTION_DATA ||
				next_work_item->section == SECTION_POST_DATA)
			{
				do_now = false;
				skipped_some = true;
			}
			else
			{
				/*
				 * SECTION_NONE items, such as comments, can be processed now
				 * if we are still in the PRE_DATA part of the archive.  Once
				 * we've skipped any items, we have to consider whether the
				 * comment's dependencies are satisfied, so skip it for now.
				 */
				if (skipped_some)
					do_now = false;
			}
		}

		/*
		 * Also skip items that need to be forced into later passes.  We need
		 * not set skipped_some in this case, since by assumption no main-pass
		 * items could depend on these.
		 */
		if (_tocEntryRestorePass(next_work_item) != RESTORE_PASS_MAIN)
			do_now = false;

		if (do_now)
		{
			/* OK, restore the item and update its dependencies */
			pg_log_info("processing item %d %s %s",
						next_work_item->dumpId,
						next_work_item->desc, next_work_item->tag);

			(void) restore_toc_entry(AH, next_work_item, false);

			/* Reduce dependencies, but don't move anything to ready_list */
			reduce_dependencies(AH, next_work_item, NULL);
		}
		else
		{
			/* Nope, so add it to pending_list */
			pending_list_append(pending_list, next_work_item);
		}
	}

	/*
	 * Now close parent connection in prep for parallel steps.  We do this
	 * mainly to ensure that we don't exceed the specified number of parallel
	 * connections.
	 */
	DisconnectDatabase(&AH->public);

	/* blow away any transient state from the old connection */
	if (AH->currUser)
		free(AH->currUser);
	AH->currUser = NULL;
	if (AH->currSchema)
		free(AH->currSchema);
	AH->currSchema = NULL;
	if (AH->currTablespace)
		free(AH->currTablespace);
	AH->currTablespace = NULL;
	if (AH->currTableAm)
		free(AH->currTableAm);
	AH->currTableAm = NULL;
}
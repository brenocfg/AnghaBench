#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  dumpId; struct TYPE_11__* pending_next; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_10__ {TYPE_3__* ropt; } ;
struct TYPE_13__ {TYPE_1__ public; } ;
struct TYPE_12__ {int /*<<< orphan*/  promptPassword; int /*<<< orphan*/  username; int /*<<< orphan*/  pgport; int /*<<< orphan*/  pghost; int /*<<< orphan*/  dbname; } ;
typedef  TYPE_3__ RestoreOptions ;
typedef  TYPE_4__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectDatabase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _doSetFixedOutputState (TYPE_4__*) ; 
 int /*<<< orphan*/  pg_log_debug (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_toc_entry (TYPE_4__*,TYPE_2__*,int) ; 

__attribute__((used)) static void
restore_toc_entries_postfork(ArchiveHandle *AH, TocEntry *pending_list)
{
	RestoreOptions *ropt = AH->public.ropt;
	TocEntry   *te;

	pg_log_debug("entering restore_toc_entries_postfork");

	/*
	 * Now reconnect the single parent connection.
	 */
	ConnectDatabase((Archive *) AH, ropt->dbname,
					ropt->pghost, ropt->pgport, ropt->username,
					ropt->promptPassword);

	/* re-establish fixed state */
	_doSetFixedOutputState(AH);

	/*
	 * Make sure there is no work left due to, say, circular dependencies, or
	 * some other pathological condition.  If so, do it in the single parent
	 * connection.  We don't sweat about RestorePass ordering; it's likely we
	 * already violated that.
	 */
	for (te = pending_list->pending_next; te != pending_list; te = te->pending_next)
	{
		pg_log_info("processing missed item %d %s %s",
					te->dumpId, te->desc, te->tag);
		(void) restore_toc_entry(AH, te, false);
	}
}
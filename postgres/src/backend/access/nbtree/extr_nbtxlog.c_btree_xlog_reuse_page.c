#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  node; int /*<<< orphan*/  latestRemovedXid; } ;
typedef  TYPE_1__ xl_btree_reuse_page ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 scalar_t__ InHotStandby ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
btree_xlog_reuse_page(XLogReaderState *record)
{
	xl_btree_reuse_page *xlrec = (xl_btree_reuse_page *) XLogRecGetData(record);

	/*
	 * Btree reuse_page records exist to provide a conflict point when we
	 * reuse pages in the index via the FSM.  That's all they do though.
	 *
	 * latestRemovedXid was the page's btpo.xact.  The btpo.xact <
	 * RecentGlobalXmin test in _bt_page_recyclable() conceptually mirrors the
	 * pgxact->xmin > limitXmin test in GetConflictingVirtualXIDs().
	 * Consequently, one XID value achieves the same exclusion effect on
	 * master and standby.
	 */
	if (InHotStandby)
	{
		ResolveRecoveryConflictWithSnapshot(xlrec->latestRemovedXid,
											xlrec->node);
	}
}
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
struct TYPE_4__ {int /*<<< orphan*/  xact; } ;
struct TYPE_5__ {TYPE_1__ btpo; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 scalar_t__ P_ISDELETED (TYPE_2__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
_bt_page_recyclable(Page page)
{
	BTPageOpaque opaque;

	/*
	 * It's possible to find an all-zeroes page in an index --- for example, a
	 * backend might successfully extend the relation one page and then crash
	 * before it is able to make a WAL entry for adding the page. If we find a
	 * zeroed page then reclaim it.
	 */
	if (PageIsNew(page))
		return true;

	/*
	 * Otherwise, recycle if deleted and too old to have any processes
	 * interested in it.
	 */
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	if (P_ISDELETED(opaque) &&
		TransactionIdPrecedes(opaque->btpo.xact, RecentGlobalXmin))
		return true;
	return false;
}
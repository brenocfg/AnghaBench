#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  PredicateLockPageSplit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PredicateLockPageCombine(Relation relation, BlockNumber oldblkno,
						 BlockNumber newblkno)
{
	/*
	 * Page combines differ from page splits in that we ought to be able to
	 * remove the locks on the old page after transferring them to the new
	 * page, instead of duplicating them. However, because we can't edit other
	 * backends' local lock tables, removing the old lock would leave them
	 * with an entry in their LocalPredicateLockHash for a lock they're not
	 * holding, which isn't acceptable. So we wind up having to do the same
	 * work as a page split, acquiring a lock on the new page and keeping the
	 * old page locked too. That can lead to some false positives, but should
	 * be rare in practice.
	 */
	PredicateLockPageSplit(relation, oldblkno, newblkno);
}
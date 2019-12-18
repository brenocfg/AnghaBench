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
struct ocfs2_quota_recovery {int dummy; } ;
struct ocfs2_la_recovery_item {int lri_slot; int lri_orphan_reco_type; int /*<<< orphan*/  lri_list; struct ocfs2_quota_recovery* lri_qrec; struct ocfs2_dinode* lri_tl_dinode; struct ocfs2_dinode* lri_la_dinode; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_lock; int /*<<< orphan*/  j_recovery_work; TYPE_1__* j_osb; int /*<<< orphan*/  j_la_cleanups; } ;
struct ocfs2_dinode {int dummy; } ;
typedef  enum ocfs2_orphan_reco_type { ____Placeholder_ocfs2_orphan_reco_type } ocfs2_orphan_reco_type ;
struct TYPE_2__ {int /*<<< orphan*/  ocfs2_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dinode*) ; 
 struct ocfs2_la_recovery_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_quota_recovery (struct ocfs2_quota_recovery*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_queue_recovery_completion(struct ocfs2_journal *journal,
					    int slot_num,
					    struct ocfs2_dinode *la_dinode,
					    struct ocfs2_dinode *tl_dinode,
					    struct ocfs2_quota_recovery *qrec,
					    enum ocfs2_orphan_reco_type orphan_reco_type)
{
	struct ocfs2_la_recovery_item *item;

	item = kmalloc(sizeof(struct ocfs2_la_recovery_item), GFP_NOFS);
	if (!item) {
		/* Though we wish to avoid it, we are in fact safe in
		 * skipping local alloc cleanup as fsck.ocfs2 is more
		 * than capable of reclaiming unused space. */
		kfree(la_dinode);
		kfree(tl_dinode);

		if (qrec)
			ocfs2_free_quota_recovery(qrec);

		mlog_errno(-ENOMEM);
		return;
	}

	INIT_LIST_HEAD(&item->lri_list);
	item->lri_la_dinode = la_dinode;
	item->lri_slot = slot_num;
	item->lri_tl_dinode = tl_dinode;
	item->lri_qrec = qrec;
	item->lri_orphan_reco_type = orphan_reco_type;

	spin_lock(&journal->j_lock);
	list_add_tail(&item->lri_list, &journal->j_la_cleanups);
	queue_work(journal->j_osb->ocfs2_wq, &journal->j_recovery_work);
	spin_unlock(&journal->j_lock);
}
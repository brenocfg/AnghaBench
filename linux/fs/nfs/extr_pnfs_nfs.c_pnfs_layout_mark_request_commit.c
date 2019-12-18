#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct list_head {int dummy; } ;
struct pnfs_commit_bucket {int /*<<< orphan*/ * wlseg; struct list_head written; } ;
struct nfs_page {int /*<<< orphan*/  wb_page; int /*<<< orphan*/  wb_flags; } ;
struct nfs_commit_info {int /*<<< orphan*/  inode; TYPE_2__* ds; TYPE_1__* completion_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  nwritten; struct pnfs_commit_bucket* buckets; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* resched_write ) (struct nfs_commit_info*,struct nfs_page*) ;} ;

/* Variables and functions */
 TYPE_3__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_COMMIT_TO_DS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mark_page_unstable (int /*<<< orphan*/ ,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_request_add_commit_list_locked (struct nfs_page*,struct list_head*,struct nfs_commit_info*) ; 
 int /*<<< orphan*/ * pnfs_get_lseg (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  pnfs_is_valid_lseg (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_commit_info*,struct nfs_page*) ; 

void
pnfs_layout_mark_request_commit(struct nfs_page *req,
				struct pnfs_layout_segment *lseg,
				struct nfs_commit_info *cinfo,
				u32 ds_commit_idx)
{
	struct list_head *list;
	struct pnfs_commit_bucket *buckets;

	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	buckets = cinfo->ds->buckets;
	list = &buckets[ds_commit_idx].written;
	if (list_empty(list)) {
		if (!pnfs_is_valid_lseg(lseg)) {
			mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
			cinfo->completion_ops->resched_write(cinfo, req);
			return;
		}
		/* Non-empty buckets hold a reference on the lseg.  That ref
		 * is normally transferred to the COMMIT call and released
		 * there.  It could also be released if the last req is pulled
		 * off due to a rewrite, in which case it will be done in
		 * pnfs_common_clear_request_commit
		 */
		WARN_ON_ONCE(buckets[ds_commit_idx].wlseg != NULL);
		buckets[ds_commit_idx].wlseg = pnfs_get_lseg(lseg);
	}
	set_bit(PG_COMMIT_TO_DS, &req->wb_flags);
	cinfo->ds->nwritten++;

	nfs_request_add_commit_list_locked(req, list, cinfo);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	nfs_mark_page_unstable(req->wb_page, cinfo);
}
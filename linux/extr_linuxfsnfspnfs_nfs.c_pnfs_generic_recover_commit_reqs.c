#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_segment {int dummy; } ;
struct pnfs_commit_bucket {struct pnfs_layout_segment* wlseg; int /*<<< orphan*/  written; } ;
struct nfs_commit_info {TYPE_1__* ds; int /*<<< orphan*/  inode; } ;
struct list_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_3__ {int nbuckets; int nwritten; struct pnfs_commit_bucket* buckets; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int nfs_scan_commit_list (int /*<<< orphan*/ *,struct list_head*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_put_lseg (struct pnfs_layout_segment*) ; 

void pnfs_generic_recover_commit_reqs(struct list_head *dst,
				      struct nfs_commit_info *cinfo)
{
	struct pnfs_commit_bucket *b;
	struct pnfs_layout_segment *freeme;
	int nwritten;
	int i;

	lockdep_assert_held(&NFS_I(cinfo->inode)->commit_mutex);
restart:
	for (i = 0, b = cinfo->ds->buckets; i < cinfo->ds->nbuckets; i++, b++) {
		nwritten = nfs_scan_commit_list(&b->written, dst, cinfo, 0);
		if (!nwritten)
			continue;
		cinfo->ds->nwritten -= nwritten;
		if (list_empty(&b->written)) {
			freeme = b->wlseg;
			b->wlseg = NULL;
			pnfs_put_lseg(freeme);
			goto restart;
		}
	}
}
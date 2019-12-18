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
struct nfs_commit_info {TYPE_1__* ds; int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_3__ {int nbuckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int pnfs_generic_scan_ds_commit_list (int /*<<< orphan*/ *,struct nfs_commit_info*,int) ; 

int pnfs_generic_scan_commit_lists(struct nfs_commit_info *cinfo,
				   int max)
{
	int i, rv = 0, cnt;

	lockdep_assert_held(&NFS_I(cinfo->inode)->commit_mutex);
	for (i = 0; i < cinfo->ds->nbuckets && max != 0; i++) {
		cnt = pnfs_generic_scan_ds_commit_list(&cinfo->ds->buckets[i],
						       cinfo, max);
		max -= cnt;
		rv += cnt;
	}
	return rv;
}
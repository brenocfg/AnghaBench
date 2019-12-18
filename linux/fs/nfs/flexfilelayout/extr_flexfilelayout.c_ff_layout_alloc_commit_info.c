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
struct pnfs_layout_segment {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  committed; } ;
struct pnfs_commit_bucket {TYPE_2__ direct_verf; int /*<<< orphan*/  committing; int /*<<< orphan*/  written; } ;
struct nfs_commit_info {TYPE_3__* inode; TYPE_1__* ds; } ;
struct nfs4_ff_layout_segment {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_lock; } ;
struct TYPE_4__ {int nbuckets; struct pnfs_commit_bucket* buckets; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nfs4_ff_layout_segment* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 int FF_LAYOUT_MIRROR_COUNT (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_INVALID_STABLE_HOW ; 
 int ff_layout_get_lseg_count (struct nfs4_ff_layout_segment*) ; 
 struct pnfs_commit_bucket* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pnfs_commit_bucket*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ff_layout_alloc_commit_info(struct pnfs_layout_segment *lseg,
			    struct nfs_commit_info *cinfo,
			    gfp_t gfp_flags)
{
	struct nfs4_ff_layout_segment *fls = FF_LAYOUT_LSEG(lseg);
	struct pnfs_commit_bucket *buckets;
	int size;

	if (cinfo->ds->nbuckets != 0) {
		/* This assumes there is only one RW lseg per file.
		 * To support multiple lseg per file, we need to
		 * change struct pnfs_commit_bucket to allow dynamic
		 * increasing nbuckets.
		 */
		return 0;
	}

	size = ff_layout_get_lseg_count(fls) * FF_LAYOUT_MIRROR_COUNT(lseg);

	buckets = kcalloc(size, sizeof(struct pnfs_commit_bucket),
			  gfp_flags);
	if (!buckets)
		return -ENOMEM;
	else {
		int i;

		spin_lock(&cinfo->inode->i_lock);
		if (cinfo->ds->nbuckets != 0)
			kfree(buckets);
		else {
			cinfo->ds->buckets = buckets;
			cinfo->ds->nbuckets = size;
			for (i = 0; i < size; i++) {
				INIT_LIST_HEAD(&buckets[i].written);
				INIT_LIST_HEAD(&buckets[i].committing);
				/* mark direct verifier as unset */
				buckets[i].direct_verf.committed =
					NFS_INVALID_STABLE_HOW;
			}
		}
		spin_unlock(&cinfo->inode->i_lock);
		return 0;
	}
}
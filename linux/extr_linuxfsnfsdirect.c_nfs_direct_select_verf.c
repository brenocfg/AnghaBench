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
struct nfs_writeverf {int dummy; } ;
struct nfs_direct_req {struct nfs_writeverf verf; } ;
struct nfs_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct nfs_writeverf *
nfs_direct_select_verf(struct nfs_direct_req *dreq,
		       struct nfs_client *ds_clp,
		       int commit_idx)
{
	struct nfs_writeverf *verfp = &dreq->verf;

#ifdef CONFIG_NFS_V4_1
	/*
	 * pNFS is in use, use the DS verf except commit_through_mds is set
	 * for layout segment where nbuckets is zero.
	 */
	if (ds_clp && dreq->ds_cinfo.nbuckets > 0) {
		if (commit_idx >= 0 && commit_idx < dreq->ds_cinfo.nbuckets)
			verfp = &dreq->ds_cinfo.buckets[commit_idx].direct_verf;
		else
			WARN_ON_ONCE(1);
	}
#endif
	return verfp;
}
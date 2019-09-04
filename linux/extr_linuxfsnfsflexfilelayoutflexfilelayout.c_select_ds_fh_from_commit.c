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
typedef  size_t u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_ff_layout_segment {TYPE_1__** mirror_array; } ;
struct TYPE_2__ {struct nfs_fh* fh_versions; } ;

/* Variables and functions */
 struct nfs4_ff_layout_segment* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 

__attribute__((used)) static struct nfs_fh *
select_ds_fh_from_commit(struct pnfs_layout_segment *lseg, u32 i)
{
	struct nfs4_ff_layout_segment *flseg = FF_LAYOUT_LSEG(lseg);

	/* FIXME: Assume that there is only one NFS version available
	 * for the DS.
	 */
	return &flseg->mirror_array[i]->fh_versions[0];
}
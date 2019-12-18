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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_filelayout_segment {scalar_t__ stripe_type; } ;

/* Variables and functions */
 struct nfs4_filelayout_segment* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 scalar_t__ STRIPE_SPARSE ; 
 int /*<<< orphan*/  nfs4_fl_calc_ds_index (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 calc_ds_index_from_commit(struct pnfs_layout_segment *lseg, u32 i)
{
	struct nfs4_filelayout_segment *flseg = FILELAYOUT_LSEG(lseg);

	if (flseg->stripe_type == STRIPE_SPARSE)
		return i;
	else
		return nfs4_fl_calc_ds_index(lseg, i);
}
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
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_pnfs_ds {int dummy; } ;
struct nfs4_ff_layout_segment {int mirror_array_cnt; } ;
struct nfs4_ff_layout_mirror {TYPE_1__* mirror_ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  id_node; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (struct pnfs_layout_segment*,int) ; 
 struct nfs4_ff_layout_segment* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 struct nfs4_pnfs_ds* nfs4_ff_layout_prepare_ds (struct pnfs_layout_segment*,struct nfs4_ff_layout_mirror*,int) ; 
 scalar_t__ nfs4_test_deviceid_unavailable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_pnfs_ds *
ff_layout_choose_ds_for_read(struct pnfs_layout_segment *lseg,
			     int start_idx, int *best_idx,
			     bool check_device)
{
	struct nfs4_ff_layout_segment *fls = FF_LAYOUT_LSEG(lseg);
	struct nfs4_ff_layout_mirror *mirror;
	struct nfs4_pnfs_ds *ds;
	bool fail_return = false;
	int idx;

	/* mirrors are initially sorted by efficiency */
	for (idx = start_idx; idx < fls->mirror_array_cnt; idx++) {
		if (idx+1 == fls->mirror_array_cnt)
			fail_return = !check_device;

		mirror = FF_LAYOUT_COMP(lseg, idx);
		ds = nfs4_ff_layout_prepare_ds(lseg, mirror, fail_return);
		if (!ds)
			continue;

		if (check_device &&
		    nfs4_test_deviceid_unavailable(&mirror->mirror_ds->id_node))
			continue;

		*best_idx = idx;
		return ds;
	}

	return NULL;
}
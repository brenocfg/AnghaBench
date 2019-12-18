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
typedef  scalar_t__ u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_ff_layout_mirror {TYPE_1__* mirror_ds; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct TYPE_2__ {struct nfs4_deviceid_node id_node; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (struct pnfs_layout_segment*,scalar_t__) ; 
 scalar_t__ FF_LAYOUT_MIRROR_COUNT (struct pnfs_layout_segment*) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs4_test_deviceid_unavailable (struct nfs4_deviceid_node*) ; 

__attribute__((used)) static bool ff_read_layout_has_available_ds(struct pnfs_layout_segment *lseg)
{
	struct nfs4_ff_layout_mirror *mirror;
	struct nfs4_deviceid_node *devid;
	u32 idx;

	for (idx = 0; idx < FF_LAYOUT_MIRROR_COUNT(lseg); idx++) {
		mirror = FF_LAYOUT_COMP(lseg, idx);
		if (mirror) {
			if (!mirror->mirror_ds)
				return true;
			if (IS_ERR(mirror->mirror_ds))
				continue;
			devid = &mirror->mirror_ds->id_node;
			if (!nfs4_test_deviceid_unavailable(devid))
				return true;
		}
	}

	return false;
}
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
struct nfs4_ff_layout_mirror {struct nfs4_ff_layout_ds* mirror_ds; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct nfs4_ff_layout_ds {struct nfs4_deviceid_node id_node; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct nfs4_ff_layout_ds*) ; 

__attribute__((used)) static inline struct nfs4_deviceid_node *
FF_LAYOUT_DEVID_NODE(struct pnfs_layout_segment *lseg, u32 idx)
{
	struct nfs4_ff_layout_mirror *mirror = FF_LAYOUT_COMP(lseg, idx);

	if (mirror != NULL) {
		struct nfs4_ff_layout_ds *mirror_ds = mirror->mirror_ds;

		if (!IS_ERR_OR_NULL(mirror_ds))
			return &mirror_ds->id_node;
	}
	return NULL;
}
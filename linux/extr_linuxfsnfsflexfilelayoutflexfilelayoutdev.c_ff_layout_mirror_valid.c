#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_segment {struct pnfs_layout_hdr* pls_layout; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_inode; int /*<<< orphan*/  plh_lc_cred; } ;
struct nfs4_ff_layout_mirror {TYPE_1__* mirror_ds; int /*<<< orphan*/  devid; } ;
struct nfs4_ff_layout_ds {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct TYPE_3__ {struct nfs4_deviceid_node id_node; int /*<<< orphan*/ * ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct nfs4_ff_layout_ds* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nfs4_ff_layout_ds* FF_LAYOUT_MIRROR_DS (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (TYPE_1__**,int /*<<< orphan*/ *,struct nfs4_ff_layout_ds*) ; 
 int /*<<< orphan*/  ff_layout_mark_devid_invalid (struct pnfs_layout_segment*,struct nfs4_deviceid_node*) ; 
 struct nfs4_deviceid_node* nfs4_find_get_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_deviceid_node (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  pnfs_error_mark_layout_for_return (int /*<<< orphan*/ ,struct pnfs_layout_segment*) ; 

__attribute__((used)) static bool ff_layout_mirror_valid(struct pnfs_layout_segment *lseg,
				   struct nfs4_ff_layout_mirror *mirror,
				   bool create)
{
	if (mirror == NULL || IS_ERR(mirror->mirror_ds))
		goto outerr;
	if (mirror->mirror_ds == NULL) {
		if (create) {
			struct nfs4_deviceid_node *node;
			struct pnfs_layout_hdr *lh = lseg->pls_layout;
			struct nfs4_ff_layout_ds *mirror_ds = ERR_PTR(-ENODEV);

			node = nfs4_find_get_deviceid(NFS_SERVER(lh->plh_inode),
					&mirror->devid, lh->plh_lc_cred,
					GFP_KERNEL);
			if (node)
				mirror_ds = FF_LAYOUT_MIRROR_DS(node);

			/* check for race with another call to this function */
			if (cmpxchg(&mirror->mirror_ds, NULL, mirror_ds) &&
			    mirror_ds != ERR_PTR(-ENODEV))
				nfs4_put_deviceid_node(node);
		} else
			goto outerr;
	}

	if (IS_ERR(mirror->mirror_ds))
		goto outerr;

	if (mirror->mirror_ds->ds == NULL) {
		struct nfs4_deviceid_node *devid;
		devid = &mirror->mirror_ds->id_node;
		ff_layout_mark_devid_invalid(lseg, devid);
		return false;
	}
	return true;
outerr:
	pnfs_error_mark_layout_for_return(lseg->pls_layout->plh_inode, lseg);
	return false;
}
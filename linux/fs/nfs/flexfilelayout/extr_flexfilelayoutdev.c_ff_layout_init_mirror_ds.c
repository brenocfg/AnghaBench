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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_lc_cred; int /*<<< orphan*/  plh_inode; } ;
struct nfs4_ff_layout_mirror {int /*<<< orphan*/ * mirror_ds; int /*<<< orphan*/  devid; } ;
struct nfs4_ff_layout_ds {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct nfs4_ff_layout_ds* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nfs4_ff_layout_ds* FF_LAYOUT_MIRROR_DS (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct nfs4_ff_layout_ds*) ; 
 struct nfs4_deviceid_node* nfs4_find_get_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_deviceid_node (struct nfs4_deviceid_node*) ; 

__attribute__((used)) static bool
ff_layout_init_mirror_ds(struct pnfs_layout_hdr *lo,
			 struct nfs4_ff_layout_mirror *mirror)
{
	if (mirror == NULL)
		goto outerr;
	if (mirror->mirror_ds == NULL) {
		struct nfs4_deviceid_node *node;
		struct nfs4_ff_layout_ds *mirror_ds = ERR_PTR(-ENODEV);

		node = nfs4_find_get_deviceid(NFS_SERVER(lo->plh_inode),
				&mirror->devid, lo->plh_lc_cred,
				GFP_KERNEL);
		if (node)
			mirror_ds = FF_LAYOUT_MIRROR_DS(node);

		/* check for race with another call to this function */
		if (cmpxchg(&mirror->mirror_ds, NULL, mirror_ds) &&
		    mirror_ds != ERR_PTR(-ENODEV))
			nfs4_put_deviceid_node(node);
	}

	if (IS_ERR(mirror->mirror_ds))
		goto outerr;

	return true;
outerr:
	return false;
}
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
struct nfs4_pnfs_ds {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  deviceid; } ;
struct nfs4_file_layout_dsaddr {int ds_num; int /*<<< orphan*/  stripe_indices; struct nfs4_pnfs_ds** ds_list; TYPE_1__ id_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 TYPE_2__ id_node ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfs4_file_layout_dsaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_pnfs_ds_put (struct nfs4_pnfs_ds*) ; 
 int /*<<< orphan*/  nfs4_print_deviceid (int /*<<< orphan*/ *) ; 

void
nfs4_fl_free_deviceid(struct nfs4_file_layout_dsaddr *dsaddr)
{
	struct nfs4_pnfs_ds *ds;
	int i;

	nfs4_print_deviceid(&dsaddr->id_node.deviceid);

	for (i = 0; i < dsaddr->ds_num; i++) {
		ds = dsaddr->ds_list[i];
		if (ds != NULL)
			nfs4_pnfs_ds_put(ds);
	}
	kfree(dsaddr->stripe_indices);
	kfree_rcu(dsaddr, id_node.rcu);
}
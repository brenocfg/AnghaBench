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
struct TYPE_3__ {int /*<<< orphan*/  deviceid; } ;
struct nfs4_ff_layout_ds {int /*<<< orphan*/  ds_versions; int /*<<< orphan*/  ds; TYPE_1__ id_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 TYPE_2__ id_node ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfs4_ff_layout_ds*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_pnfs_ds_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_print_deviceid (int /*<<< orphan*/ *) ; 

void nfs4_ff_layout_free_deviceid(struct nfs4_ff_layout_ds *mirror_ds)
{
	nfs4_print_deviceid(&mirror_ds->id_node.deviceid);
	nfs4_pnfs_ds_put(mirror_ds->ds);
	kfree(mirror_ds->ds_versions);
	kfree_rcu(mirror_ds, id_node.rcu);
}
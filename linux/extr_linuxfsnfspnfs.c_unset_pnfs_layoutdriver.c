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
struct nfs_server {TYPE_1__* pnfs_curr_ld; TYPE_2__* nfs_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_mds_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* clear_layoutdriver ) (struct nfs_server*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_deviceid_purge_client (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_server*) ; 

void
unset_pnfs_layoutdriver(struct nfs_server *nfss)
{
	if (nfss->pnfs_curr_ld) {
		if (nfss->pnfs_curr_ld->clear_layoutdriver)
			nfss->pnfs_curr_ld->clear_layoutdriver(nfss);
		/* Decrement the MDS count. Purge the deviceid cache if zero */
		if (atomic_dec_and_test(&nfss->nfs_client->cl_mds_count))
			nfs4_deviceid_purge_client(nfss->nfs_client);
		module_put(nfss->pnfs_curr_ld->owner);
	}
	nfss->pnfs_curr_ld = NULL;
}
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
struct nfs_client {struct nfs4_slot_table* cl_slot_tbl; } ;
struct nfs4_slot_table {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NFS4_MAX_SLOT_TABLE ; 
 int /*<<< orphan*/  kfree (struct nfs4_slot_table*) ; 
 struct nfs4_slot_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfs4_setup_slot_table (struct nfs4_slot_table*,int /*<<< orphan*/ ,char*) ; 

int nfs40_init_client(struct nfs_client *clp)
{
	struct nfs4_slot_table *tbl;
	int ret;

	tbl = kzalloc(sizeof(*tbl), GFP_NOFS);
	if (tbl == NULL)
		return -ENOMEM;

	ret = nfs4_setup_slot_table(tbl, NFS4_MAX_SLOT_TABLE,
					"NFSv4.0 transport Slot table");
	if (ret) {
		kfree(tbl);
		return ret;
	}

	clp->cl_slot_tbl = tbl;
	return 0;
}
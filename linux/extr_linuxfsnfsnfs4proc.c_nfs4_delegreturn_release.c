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
struct TYPE_4__ {int /*<<< orphan*/  lr_ret; } ;
struct TYPE_3__ {int /*<<< orphan*/  res; int /*<<< orphan*/  arg; scalar_t__ roc; } ;
struct nfs4_delegreturndata {int /*<<< orphan*/  fattr; TYPE_2__ res; TYPE_1__ lr; struct inode* inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  nfs_iput_and_deactive (struct inode*) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode_force_wcc (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_roc_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_delegreturn_release(void *calldata)
{
	struct nfs4_delegreturndata *data = calldata;
	struct inode *inode = data->inode;

	if (inode) {
		if (data->lr.roc)
			pnfs_roc_release(&data->lr.arg, &data->lr.res,
					data->res.lr_ret);
		nfs_post_op_update_inode_force_wcc(inode, &data->fattr);
		nfs_iput_and_deactive(inode);
	}
	kfree(calldata);
}
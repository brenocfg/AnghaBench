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
struct rpc_task {int dummy; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_flags; } ;
struct nfs_inode {struct pnfs_layout_hdr* layout; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  roc_rpcwaitq; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool pnfs_wait_on_layoutreturn(struct inode *ino, struct rpc_task *task)
{
	struct nfs_inode *nfsi = NFS_I(ino);
        struct pnfs_layout_hdr *lo;
        bool sleep = false;

	/* we might not have grabbed lo reference. so need to check under
	 * i_lock */
        spin_lock(&ino->i_lock);
        lo = nfsi->layout;
        if (lo && test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags)) {
                rpc_sleep_on(&NFS_SERVER(ino)->roc_rpcwaitq, task, NULL);
                sleep = true;
	}
        spin_unlock(&ino->i_lock);
        return sleep;
}
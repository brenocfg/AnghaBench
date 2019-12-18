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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_inode; int /*<<< orphan*/  plh_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  roc_rpcwaitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_RETURN ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN_LOCK ; 
 TYPE_1__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnfs_clear_layoutreturn_waitbit(struct pnfs_layout_hdr *lo)
{
	clear_bit_unlock(NFS_LAYOUT_RETURN, &lo->plh_flags);
	clear_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags);
	smp_mb__after_atomic();
	wake_up_bit(&lo->plh_flags, NFS_LAYOUT_RETURN);
	rpc_wake_up(&NFS_SERVER(lo->plh_inode)->roc_rpcwaitq);
}
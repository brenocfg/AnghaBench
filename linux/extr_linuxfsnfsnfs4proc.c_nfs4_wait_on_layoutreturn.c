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
struct rpc_task {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_have_layout (struct inode*) ; 
 int pnfs_wait_on_layoutreturn (struct inode*,struct rpc_task*) ; 

__attribute__((used)) static bool
nfs4_wait_on_layoutreturn(struct inode *inode, struct rpc_task *task)
{
	if (inode == NULL || !nfs_have_layout(inode))
		return false;

	return pnfs_wait_on_layoutreturn(inode, task);
}
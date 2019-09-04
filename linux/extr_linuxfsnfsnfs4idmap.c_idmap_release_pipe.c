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
struct rpc_inode {scalar_t__ private; } ;
struct inode {int dummy; } ;
struct idmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 struct rpc_inode* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  nfs_idmap_abort_pipe_upcall (struct idmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idmap_release_pipe(struct inode *inode)
{
	struct rpc_inode *rpci = RPC_I(inode);
	struct idmap *idmap = (struct idmap *)rpci->private;

	nfs_idmap_abort_pipe_upcall(idmap, -EPIPE);
}
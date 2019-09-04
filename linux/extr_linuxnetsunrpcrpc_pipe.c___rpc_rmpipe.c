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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int __rpc_unlink (struct inode*,struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  rpc_close_pipes (struct inode*) ; 

__attribute__((used)) static int __rpc_rmpipe(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);

	rpc_close_pipes(inode);
	return __rpc_unlink(dir, dentry);
}
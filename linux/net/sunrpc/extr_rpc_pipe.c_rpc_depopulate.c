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
struct rpc_filelist {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  __rpc_depopulate (struct dentry*,struct rpc_filelist const*,int,int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static void rpc_depopulate(struct dentry *parent,
			   const struct rpc_filelist *files,
			   int start, int eof)
{
	struct inode *dir = d_inode(parent);

	inode_lock_nested(dir, I_MUTEX_CHILD);
	__rpc_depopulate(parent, files, start, eof);
	inode_unlock(dir);
}
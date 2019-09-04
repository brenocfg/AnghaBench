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
typedef  int umode_t ;
struct rpc_pipe {int dummy; } ;
struct rpc_inode {struct rpc_pipe* pipe; void* private; } ;
struct inode {int dummy; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct rpc_inode* RPC_I (int /*<<< orphan*/ ) ; 
 int S_IFIFO ; 
 int __rpc_create_common (struct inode*,struct dentry*,int,struct file_operations const*,void*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 

__attribute__((used)) static int __rpc_mkpipe_dentry(struct inode *dir, struct dentry *dentry,
			       umode_t mode,
			       const struct file_operations *i_fop,
			       void *private,
			       struct rpc_pipe *pipe)
{
	struct rpc_inode *rpci;
	int err;

	err = __rpc_create_common(dir, dentry, S_IFIFO | mode, i_fop, private);
	if (err)
		return err;
	rpci = RPC_I(d_inode(dentry));
	rpci->private = private;
	rpci->pipe = pipe;
	fsnotify_create(dir, dentry);
	return 0;
}
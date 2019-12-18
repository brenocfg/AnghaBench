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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_depopulate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __rpc_rmpipe (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  gssd_dummy_clnt_dir ; 
 int /*<<< orphan*/  gssd_dummy_info_file ; 

__attribute__((used)) static void
rpc_gssd_dummy_depopulate(struct dentry *pipe_dentry)
{
	struct dentry *clnt_dir = pipe_dentry->d_parent;
	struct dentry *gssd_dir = clnt_dir->d_parent;

	dget(pipe_dentry);
	__rpc_rmpipe(d_inode(clnt_dir), pipe_dentry);
	__rpc_depopulate(clnt_dir, gssd_dummy_info_file, 0, 1);
	__rpc_depopulate(gssd_dir, gssd_dummy_clnt_dir, 0, 1);
	dput(pipe_dentry);
}
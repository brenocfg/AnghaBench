#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct rpc_clnt* private; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_count; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_2__* dentry; } ;
struct file {TYPE_1__ f_path; struct seq_file* private_data; } ;
struct TYPE_6__ {struct rpc_clnt* private; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__* RPC_I (struct inode*) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_unhashed (TYPE_2__*) ; 
 int /*<<< orphan*/  rpc_show_info ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  single_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rpc_info_open(struct inode *inode, struct file *file)
{
	struct rpc_clnt *clnt = NULL;
	int ret = single_open(file, rpc_show_info, NULL);

	if (!ret) {
		struct seq_file *m = file->private_data;

		spin_lock(&file->f_path.dentry->d_lock);
		if (!d_unhashed(file->f_path.dentry))
			clnt = RPC_I(inode)->private;
		if (clnt != NULL && atomic_inc_not_zero(&clnt->cl_count)) {
			spin_unlock(&file->f_path.dentry->d_lock);
			m->private = clnt;
		} else {
			spin_unlock(&file->f_path.dentry->d_lock);
			single_release(inode, file);
			ret = -EINVAL;
		}
	}
	return ret;
}
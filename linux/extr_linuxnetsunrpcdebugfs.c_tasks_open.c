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
struct seq_file {struct rpc_clnt* private; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_count; } ;
struct inode {struct rpc_clnt* i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  tasks_seq_operations ; 

__attribute__((used)) static int tasks_open(struct inode *inode, struct file *filp)
{
	int ret = seq_open(filp, &tasks_seq_operations);
	if (!ret) {
		struct seq_file *seq = filp->private_data;
		struct rpc_clnt *clnt = seq->private = inode->i_private;

		if (!atomic_inc_not_zero(&clnt->cl_count)) {
			seq_release(inode, filp);
			ret = -EINVAL;
		}
	}

	return ret;
}
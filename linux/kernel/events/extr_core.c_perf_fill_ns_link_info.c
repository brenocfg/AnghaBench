#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct proc_ns_operations {int dummy; } ;
struct perf_ns_link_info {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;
struct path {TYPE_1__* dentry; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_2__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 void* ns_get_path (struct path*,struct task_struct*,struct proc_ns_operations const*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

__attribute__((used)) static void perf_fill_ns_link_info(struct perf_ns_link_info *ns_link_info,
				   struct task_struct *task,
				   const struct proc_ns_operations *ns_ops)
{
	struct path ns_path;
	struct inode *ns_inode;
	void *error;

	error = ns_get_path(&ns_path, task, ns_ops);
	if (!error) {
		ns_inode = ns_path.dentry->d_inode;
		ns_link_info->dev = new_encode_dev(ns_inode->i_sb->s_dev);
		ns_link_info->ino = ns_inode->i_ino;
		path_put(&ns_path);
	}
}
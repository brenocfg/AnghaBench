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
struct poll_table_struct {int dummy; } ;
struct file_operations {int /*<<< orphan*/  (* poll ) (struct file*,struct poll_table_struct*) ;} ;
struct file {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLHUP ; 
 struct dentry* F_DENTRY (struct file*) ; 
 scalar_t__ debugfs_file_get (struct dentry*) ; 
 int /*<<< orphan*/  debugfs_file_put (struct dentry*) ; 
 struct file_operations* debugfs_real_fops (struct file*) ; 
 int /*<<< orphan*/  stub1 (struct file*,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t full_proxy_poll(struct file *filp,
				struct poll_table_struct *wait)
{
	struct dentry *dentry = F_DENTRY(filp);
	__poll_t r = 0;
	const struct file_operations *real_fops;

	if (debugfs_file_get(dentry))
		return EPOLLHUP;

	real_fops = debugfs_real_fops(filp);
	r = real_fops->poll(filp, wait);
	debugfs_file_put(dentry);
	return r;
}
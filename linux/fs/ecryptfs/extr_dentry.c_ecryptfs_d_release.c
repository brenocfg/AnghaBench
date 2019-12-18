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
struct ecryptfs_dentry_info {int /*<<< orphan*/  rcu; int /*<<< orphan*/  lower_path; } ;
struct dentry {struct ecryptfs_dentry_info* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_dentry_free_rcu ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecryptfs_d_release(struct dentry *dentry)
{
	struct ecryptfs_dentry_info *p = dentry->d_fsdata;
	if (p) {
		path_put(&p->lower_path);
		call_rcu(&p->rcu, ecryptfs_dentry_free_rcu);
	}
}
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
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  autofs_del_expiring (struct dentry*) ; 
 int autofs_expire_wait (struct path const*,int) ; 
 struct dentry* autofs_lookup_expiring (struct dentry*,int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static int do_expire_wait(const struct path *path, bool rcu_walk)
{
	struct dentry *dentry = path->dentry;
	struct dentry *expiring;

	expiring = autofs_lookup_expiring(dentry, rcu_walk);
	if (IS_ERR(expiring))
		return PTR_ERR(expiring);
	if (!expiring)
		return autofs_expire_wait(path, rcu_walk);
	else {
		const struct path this = { .mnt = path->mnt, .dentry = expiring };
		/*
		 * If we are racing with expire the request might not
		 * be quite complete, but the directory has been removed
		 * so it must have been successful, just wait for it.
		 */
		autofs_expire_wait(&this, 0);
		autofs_del_expiring(expiring);
		dput(expiring);
	}
	return 0;
}
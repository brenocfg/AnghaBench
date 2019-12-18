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
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_disconnected(struct dentry *dentry)
{
	dget(dentry);
	while (dentry->d_flags & DCACHE_DISCONNECTED) {
		struct dentry *parent = dget_parent(dentry);

		WARN_ON_ONCE(IS_ROOT(dentry));

		spin_lock(&dentry->d_lock);
		dentry->d_flags &= ~DCACHE_DISCONNECTED;
		spin_unlock(&dentry->d_lock);

		dput(dentry);
		dentry = parent;
	}
	dput(dentry);
}
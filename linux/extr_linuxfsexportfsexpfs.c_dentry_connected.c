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
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static bool dentry_connected(struct dentry *dentry)
{
	dget(dentry);
	while (dentry->d_flags & DCACHE_DISCONNECTED) {
		struct dentry *parent = dget_parent(dentry);

		dput(dentry);
		if (dentry == parent) {
			dput(parent);
			return false;
		}
		dentry = parent;
	}
	dput(dentry);
	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct dentry {int d_flags; TYPE_1__ d_lockref; int /*<<< orphan*/  d_inode; } ;
typedef  enum d_walk_ret { ____Placeholder_d_walk_ret } d_walk_ret ;

/* Variables and functions */
 int DCACHE_GENOCIDE ; 
 int D_WALK_CONTINUE ; 
 int D_WALK_SKIP ; 
 scalar_t__ d_unhashed (struct dentry*) ; 

__attribute__((used)) static enum d_walk_ret d_genocide_kill(void *data, struct dentry *dentry)
{
	struct dentry *root = data;
	if (dentry != root) {
		if (d_unhashed(dentry) || !dentry->d_inode)
			return D_WALK_SKIP;

		if (!(dentry->d_flags & DCACHE_GENOCIDE)) {
			dentry->d_flags |= DCACHE_GENOCIDE;
			dentry->d_lockref.count--;
		}
	}
	return D_WALK_CONTINUE;
}
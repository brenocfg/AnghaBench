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
struct dentry {int dummy; } ;

/* Variables and functions */
 int d_count (struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 

__attribute__((used)) static bool nilfs_tree_is_busy(struct dentry *root_dentry)
{
	shrink_dcache_parent(root_dentry);
	return d_count(root_dentry) > 1;
}
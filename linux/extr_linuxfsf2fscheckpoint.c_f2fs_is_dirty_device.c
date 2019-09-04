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
struct inode_management {int /*<<< orphan*/  ino_lock; int /*<<< orphan*/  ino_root; } ;
struct ino_entry {int /*<<< orphan*/  dirty_device; } ;
struct f2fs_sb_info {struct inode_management* im; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 scalar_t__ f2fs_test_bit (unsigned int,char*) ; 
 struct ino_entry* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool f2fs_is_dirty_device(struct f2fs_sb_info *sbi, nid_t ino,
					unsigned int devidx, int type)
{
	struct inode_management *im = &sbi->im[type];
	struct ino_entry *e;
	bool is_dirty = false;

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	if (e && f2fs_test_bit(devidx, (char *)&e->dirty_device))
		is_dirty = true;
	spin_unlock(&im->ino_lock);
	return is_dirty;
}
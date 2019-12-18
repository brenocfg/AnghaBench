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
struct inode_management {int /*<<< orphan*/  ino_lock; int /*<<< orphan*/  ino_num; int /*<<< orphan*/  ino_root; } ;
struct ino_entry {int /*<<< orphan*/  list; } ;
struct f2fs_sb_info {struct inode_management* im; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ino_entry_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ino_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ino_entry* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_ino_entry(struct f2fs_sb_info *sbi, nid_t ino, int type)
{
	struct inode_management *im = &sbi->im[type];
	struct ino_entry *e;

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	if (e) {
		list_del(&e->list);
		radix_tree_delete(&im->ino_root, ino);
		im->ino_num--;
		spin_unlock(&im->ino_lock);
		kmem_cache_free(ino_entry_slab, e);
		return;
	}
	spin_unlock(&im->ino_lock);
}
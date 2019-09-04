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
struct inode_management {int /*<<< orphan*/  ino_lock; int /*<<< orphan*/  ino_num; int /*<<< orphan*/  ino_list; int /*<<< orphan*/  ino_root; } ;
struct ino_entry {int /*<<< orphan*/  dirty_device; int /*<<< orphan*/  list; int /*<<< orphan*/  ino; } ;
struct f2fs_sb_info {struct inode_management* im; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int FLUSH_INO ; 
 int GFP_NOFS ; 
 int ORPHAN_INO ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 struct ino_entry* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_set_bit (unsigned int,char*) ; 
 int /*<<< orphan*/  ino_entry_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ino_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ino_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ino_entry*) ; 
 struct ino_entry* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __add_ino_entry(struct f2fs_sb_info *sbi, nid_t ino,
						unsigned int devidx, int type)
{
	struct inode_management *im = &sbi->im[type];
	struct ino_entry *e, *tmp;

	tmp = f2fs_kmem_cache_alloc(ino_entry_slab, GFP_NOFS);

	radix_tree_preload(GFP_NOFS | __GFP_NOFAIL);

	spin_lock(&im->ino_lock);
	e = radix_tree_lookup(&im->ino_root, ino);
	if (!e) {
		e = tmp;
		if (unlikely(radix_tree_insert(&im->ino_root, ino, e)))
			f2fs_bug_on(sbi, 1);

		memset(e, 0, sizeof(struct ino_entry));
		e->ino = ino;

		list_add_tail(&e->list, &im->ino_list);
		if (type != ORPHAN_INO)
			im->ino_num++;
	}

	if (type == FLUSH_INO)
		f2fs_set_bit(devidx, (char *)&e->dirty_device);

	spin_unlock(&im->ino_lock);
	radix_tree_preload_end();

	if (e != tmp)
		kmem_cache_free(ino_entry_slab, tmp);
}
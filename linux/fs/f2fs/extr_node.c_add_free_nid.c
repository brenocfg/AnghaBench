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
struct nat_entry {int dummy; } ;
struct free_nid {scalar_t__ state; int /*<<< orphan*/  nid; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  available_nids; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FREE_NID ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  IS_CHECKPOINTED ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ NULL_ADDR ; 
 int __GFP_NOFAIL ; 
 int __insert_free_nid (struct f2fs_sb_info*,struct free_nid*,scalar_t__) ; 
 struct free_nid* __lookup_free_nid_list (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 struct nat_entry* __lookup_nat_cache (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 int f2fs_check_nid_range (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct free_nid* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_nid_slab ; 
 int /*<<< orphan*/  get_nat_flag (struct nat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct free_nid*) ; 
 scalar_t__ nat_get_blkaddr (struct nat_entry*) ; 
 int /*<<< orphan*/  radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_free_nid_bitmap (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool add_free_nid(struct f2fs_sb_info *sbi,
				nid_t nid, bool build, bool update)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct free_nid *i, *e;
	struct nat_entry *ne;
	int err = -EINVAL;
	bool ret = false;

	/* 0 nid should not be used */
	if (unlikely(nid == 0))
		return false;

	if (unlikely(f2fs_check_nid_range(sbi, nid)))
		return false;

	i = f2fs_kmem_cache_alloc(free_nid_slab, GFP_NOFS);
	i->nid = nid;
	i->state = FREE_NID;

	radix_tree_preload(GFP_NOFS | __GFP_NOFAIL);

	spin_lock(&nm_i->nid_list_lock);

	if (build) {
		/*
		 *   Thread A             Thread B
		 *  - f2fs_create
		 *   - f2fs_new_inode
		 *    - f2fs_alloc_nid
		 *     - __insert_nid_to_list(PREALLOC_NID)
		 *                     - f2fs_balance_fs_bg
		 *                      - f2fs_build_free_nids
		 *                       - __f2fs_build_free_nids
		 *                        - scan_nat_page
		 *                         - add_free_nid
		 *                          - __lookup_nat_cache
		 *  - f2fs_add_link
		 *   - f2fs_init_inode_metadata
		 *    - f2fs_new_inode_page
		 *     - f2fs_new_node_page
		 *      - set_node_addr
		 *  - f2fs_alloc_nid_done
		 *   - __remove_nid_from_list(PREALLOC_NID)
		 *                         - __insert_nid_to_list(FREE_NID)
		 */
		ne = __lookup_nat_cache(nm_i, nid);
		if (ne && (!get_nat_flag(ne, IS_CHECKPOINTED) ||
				nat_get_blkaddr(ne) != NULL_ADDR))
			goto err_out;

		e = __lookup_free_nid_list(nm_i, nid);
		if (e) {
			if (e->state == FREE_NID)
				ret = true;
			goto err_out;
		}
	}
	ret = true;
	err = __insert_free_nid(sbi, i, FREE_NID);
err_out:
	if (update) {
		update_free_nid_bitmap(sbi, nid, ret, build);
		if (!build)
			nm_i->available_nids++;
	}
	spin_unlock(&nm_i->nid_list_lock);
	radix_tree_preload_end();

	if (err)
		kmem_cache_free(free_nid_slab, i);
	return ret;
}
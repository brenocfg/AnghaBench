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
struct free_nid {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  available_nids; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_NID ; 
 int /*<<< orphan*/  FREE_NIDS ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  PREALLOC_NID ; 
 struct free_nid* __lookup_free_nid_list (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __move_free_nid (struct f2fs_sb_info*,struct free_nid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __remove_free_nid (struct f2fs_sb_info*,struct free_nid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  free_nid_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct free_nid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_free_nid_bitmap (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int) ; 

void f2fs_alloc_nid_failed(struct f2fs_sb_info *sbi, nid_t nid)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct free_nid *i;
	bool need_free = false;

	if (!nid)
		return;

	spin_lock(&nm_i->nid_list_lock);
	i = __lookup_free_nid_list(nm_i, nid);
	f2fs_bug_on(sbi, !i);

	if (!f2fs_available_free_memory(sbi, FREE_NIDS)) {
		__remove_free_nid(sbi, i, PREALLOC_NID);
		need_free = true;
	} else {
		__move_free_nid(sbi, i, PREALLOC_NID, FREE_NID);
	}

	nm_i->available_nids++;

	update_free_nid_bitmap(sbi, nid, true, false);

	spin_unlock(&nm_i->nid_list_lock);

	if (need_free)
		kmem_cache_free(free_nid_slab, i);
}
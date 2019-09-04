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
struct f2fs_nm_info {int /*<<< orphan*/  nid_list_lock; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  PREALLOC_NID ; 
 struct free_nid* __lookup_free_nid_list (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __remove_free_nid (struct f2fs_sb_info*,struct free_nid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  free_nid_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct free_nid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void f2fs_alloc_nid_done(struct f2fs_sb_info *sbi, nid_t nid)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct free_nid *i;

	spin_lock(&nm_i->nid_list_lock);
	i = __lookup_free_nid_list(nm_i, nid);
	f2fs_bug_on(sbi, !i);
	__remove_free_nid(sbi, i, PREALLOC_NID);
	spin_unlock(&nm_i->nid_list_lock);

	kmem_cache_free(free_nid_slab, i);
}
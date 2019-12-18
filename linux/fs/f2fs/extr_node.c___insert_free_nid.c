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
struct free_nid {int state; int /*<<< orphan*/  list; int /*<<< orphan*/  nid; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  free_nid_list; int /*<<< orphan*/ * nid_cnt; int /*<<< orphan*/  free_nid_root; } ;
typedef  enum nid_state { ____Placeholder_nid_state } nid_state ;

/* Variables and functions */
 int FREE_NID ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct free_nid*) ; 

__attribute__((used)) static int __insert_free_nid(struct f2fs_sb_info *sbi,
			struct free_nid *i, enum nid_state state)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);

	int err = radix_tree_insert(&nm_i->free_nid_root, i->nid, i);
	if (err)
		return err;

	f2fs_bug_on(sbi, state != i->state);
	nm_i->nid_cnt[state]++;
	if (state == FREE_NID)
		list_add_tail(&i->list, &nm_i->free_nid_list);
	return 0;
}
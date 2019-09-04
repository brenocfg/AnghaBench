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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  available_nids; } ;
struct f2fs_nat_entry {int /*<<< orphan*/  block_addr; } ;
struct f2fs_journal {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  journal_rwsem; struct f2fs_journal* journal; } ;
typedef  scalar_t__ nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURSEG_HOT_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_DIRTY ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ NULL_ADDR ; 
 struct nat_entry* __alloc_nat_entry (scalar_t__,int) ; 
 int /*<<< orphan*/  __init_nat_entry (struct f2fs_nm_info*,struct nat_entry*,struct f2fs_nat_entry*,int) ; 
 struct nat_entry* __lookup_nat_cache (struct f2fs_nm_info*,scalar_t__) ; 
 int /*<<< orphan*/  __set_nat_cache_dirty (struct f2fs_nm_info*,struct nat_entry*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_nat_flag (struct nat_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct f2fs_nat_entry nat_in_journal (struct f2fs_journal*,int) ; 
 int nats_in_cursum (struct f2fs_journal*) ; 
 int /*<<< orphan*/  nid_in_journal (struct f2fs_journal*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_nats_in_cursum (struct f2fs_journal*,int) ; 

__attribute__((used)) static void remove_nats_in_journal(struct f2fs_sb_info *sbi)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	struct f2fs_journal *journal = curseg->journal;
	int i;

	down_write(&curseg->journal_rwsem);
	for (i = 0; i < nats_in_cursum(journal); i++) {
		struct nat_entry *ne;
		struct f2fs_nat_entry raw_ne;
		nid_t nid = le32_to_cpu(nid_in_journal(journal, i));

		raw_ne = nat_in_journal(journal, i);

		ne = __lookup_nat_cache(nm_i, nid);
		if (!ne) {
			ne = __alloc_nat_entry(nid, true);
			__init_nat_entry(nm_i, ne, &raw_ne, true);
		}

		/*
		 * if a free nat in journal has not been used after last
		 * checkpoint, we should remove it from available nids,
		 * since later we will add it again.
		 */
		if (!get_nat_flag(ne, IS_DIRTY) &&
				le32_to_cpu(raw_ne.block_addr) == NULL_ADDR) {
			spin_lock(&nm_i->nid_list_lock);
			nm_i->available_nids--;
			spin_unlock(&nm_i->nid_list_lock);
		}

		__set_nat_cache_dirty(nm_i, ne);
	}
	update_nats_in_cursum(journal, -i);
	up_write(&curseg->journal_rwsem);
}
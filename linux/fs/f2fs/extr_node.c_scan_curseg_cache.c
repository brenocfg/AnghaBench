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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_journal {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  journal_rwsem; struct f2fs_journal* journal; } ;
typedef  void* nid_t ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {int /*<<< orphan*/  block_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSEG_HOT_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  add_free_nid (struct f2fs_sb_info*,void*,int,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__ nat_in_journal (struct f2fs_journal*,int) ; 
 int nats_in_cursum (struct f2fs_journal*) ; 
 int /*<<< orphan*/  nid_in_journal (struct f2fs_journal*,int) ; 
 int /*<<< orphan*/  remove_free_nid (struct f2fs_sb_info*,void*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scan_curseg_cache(struct f2fs_sb_info *sbi)
{
	struct curseg_info *curseg = CURSEG_I(sbi, CURSEG_HOT_DATA);
	struct f2fs_journal *journal = curseg->journal;
	int i;

	down_read(&curseg->journal_rwsem);
	for (i = 0; i < nats_in_cursum(journal); i++) {
		block_t addr;
		nid_t nid;

		addr = le32_to_cpu(nat_in_journal(journal, i).block_addr);
		nid = le32_to_cpu(nid_in_journal(journal, i));
		if (addr == NULL_ADDR)
			add_free_nid(sbi, nid, true, false);
		else
			remove_free_nid(sbi, nid);
	}
	up_read(&curseg->journal_rwsem);
}
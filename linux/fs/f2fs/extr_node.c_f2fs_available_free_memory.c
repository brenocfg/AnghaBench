#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sysinfo {int totalram; unsigned long totalhigh; } ;
struct nat_entry {int dummy; } ;
struct ino_entry {int dummy; } ;
struct free_nid {int dummy; } ;
struct f2fs_sb_info {TYPE_4__* sb; int /*<<< orphan*/  total_ext_node; int /*<<< orphan*/  total_ext_tree; TYPE_1__* im; } ;
struct f2fs_nm_info {int* nid_cnt; unsigned long ram_thresh; int nat_cnt; } ;
struct extent_tree {int dummy; } ;
struct extent_node {int dummy; } ;
struct TYPE_8__ {TYPE_3__* s_bdi; } ;
struct TYPE_6__ {scalar_t__ dirty_exceeded; } ;
struct TYPE_7__ {TYPE_2__ wb; } ;
struct TYPE_5__ {int ino_num; } ;

/* Variables and functions */
 int DIRTY_DENTS ; 
 int EXTENT_CACHE ; 
 int /*<<< orphan*/  F2FS_DIRTY_DENTS ; 
 int /*<<< orphan*/  F2FS_INMEM_PAGES ; 
 size_t FREE_NID ; 
 int FREE_NIDS ; 
 int INMEM_PAGES ; 
 int INO_ENTRIES ; 
 int MAX_INO_ENTRY ; 
 int NAT_ENTRIES ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int PAGE_SHIFT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ excess_cached_nats (struct f2fs_sb_info*) ; 
 unsigned long get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

bool f2fs_available_free_memory(struct f2fs_sb_info *sbi, int type)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct sysinfo val;
	unsigned long avail_ram;
	unsigned long mem_size = 0;
	bool res = false;

	si_meminfo(&val);

	/* only uses low memory */
	avail_ram = val.totalram - val.totalhigh;

	/*
	 * give 25%, 25%, 50%, 50%, 50% memory for each components respectively
	 */
	if (type == FREE_NIDS) {
		mem_size = (nm_i->nid_cnt[FREE_NID] *
				sizeof(struct free_nid)) >> PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 2);
	} else if (type == NAT_ENTRIES) {
		mem_size = (nm_i->nat_cnt * sizeof(struct nat_entry)) >>
							PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 2);
		if (excess_cached_nats(sbi))
			res = false;
	} else if (type == DIRTY_DENTS) {
		if (sbi->sb->s_bdi->wb.dirty_exceeded)
			return false;
		mem_size = get_pages(sbi, F2FS_DIRTY_DENTS);
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	} else if (type == INO_ENTRIES) {
		int i;

		for (i = 0; i < MAX_INO_ENTRY; i++)
			mem_size += sbi->im[i].ino_num *
						sizeof(struct ino_entry);
		mem_size >>= PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	} else if (type == EXTENT_CACHE) {
		mem_size = (atomic_read(&sbi->total_ext_tree) *
				sizeof(struct extent_tree) +
				atomic_read(&sbi->total_ext_node) *
				sizeof(struct extent_node)) >> PAGE_SHIFT;
		res = mem_size < ((avail_ram * nm_i->ram_thresh / 100) >> 1);
	} else if (type == INMEM_PAGES) {
		/* it allows 20% / total_ram for inmemory pages */
		mem_size = get_pages(sbi, F2FS_INMEM_PAGES);
		res = mem_size < (val.totalram / 5);
	} else {
		if (!sbi->sb->s_bdi->wb.dirty_exceeded)
			return true;
	}
	return res;
}
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
struct seg_entry {int dummy; } ;
struct page {int dummy; } ;
struct f2fs_sit_entry {int dummy; } ;
struct f2fs_sit_block {struct f2fs_sit_entry* entries; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAIN_SEGS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ SIT_ENTRY_PER_BLOCK ; 
 int /*<<< orphan*/  __seg_info_to_raw_sit (struct seg_entry*,struct f2fs_sit_entry*) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct f2fs_sit_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (scalar_t__,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static inline void seg_info_to_sit_page(struct f2fs_sb_info *sbi,
				struct page *page, unsigned int start)
{
	struct f2fs_sit_block *raw_sit;
	struct seg_entry *se;
	struct f2fs_sit_entry *rs;
	unsigned int end = min(start + SIT_ENTRY_PER_BLOCK,
					(unsigned long)MAIN_SEGS(sbi));
	int i;

	raw_sit = (struct f2fs_sit_block *)page_address(page);
	memset(raw_sit, 0, PAGE_SIZE);
	for (i = 0; i < end - start; i++) {
		rs = &raw_sit->entries[i];
		se = get_seg_entry(sbi, start + i);
		__seg_info_to_raw_sit(se, rs);
	}
}
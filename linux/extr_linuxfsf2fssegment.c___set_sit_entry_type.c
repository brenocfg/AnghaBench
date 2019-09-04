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
struct seg_entry {int type; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mark_sit_entry_dirty (struct f2fs_sb_info*,unsigned int) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static void __set_sit_entry_type(struct f2fs_sb_info *sbi, int type,
					unsigned int segno, int modified)
{
	struct seg_entry *se = get_seg_entry(sbi, segno);
	se->type = type;
	if (modified)
		__mark_sit_entry_dirty(sbi, segno);
}
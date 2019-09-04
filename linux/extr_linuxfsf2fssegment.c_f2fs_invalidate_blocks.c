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
struct sit_info {int /*<<< orphan*/  sentry_lock; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 unsigned int GET_SEGNO (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  locate_dirty_segment (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_sit_entry (struct f2fs_sb_info*,scalar_t__,int) ; 

void f2fs_invalidate_blocks(struct f2fs_sb_info *sbi, block_t addr)
{
	unsigned int segno = GET_SEGNO(sbi, addr);
	struct sit_info *sit_i = SIT_I(sbi);

	f2fs_bug_on(sbi, addr == NULL_ADDR);
	if (addr == NEW_ADDR)
		return;

	invalidate_mapping_pages(META_MAPPING(sbi), addr, addr);

	/* add it into sit main buffer */
	down_write(&sit_i->sentry_lock);

	update_sit_entry(sbi, addr, -1);

	/* add it into dirty seglist */
	locate_dirty_segment(sbi, segno);

	up_write(&sit_i->sentry_lock);
}
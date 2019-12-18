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
struct f2fs_sb_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  gc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SBI_IS_DIRTY ; 
 int /*<<< orphan*/  clear_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_dirty_to_prefree (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_enable_checkpoint(struct f2fs_sb_info *sbi)
{
	mutex_lock(&sbi->gc_mutex);
	f2fs_dirty_to_prefree(sbi);

	clear_sbi_flag(sbi, SBI_CP_DISABLED);
	set_sbi_flag(sbi, SBI_IS_DIRTY);
	mutex_unlock(&sbi->gc_mutex);

	f2fs_sync_fs(sbi->sb, 1);
}
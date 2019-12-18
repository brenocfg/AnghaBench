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
struct dirty_seglist_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dirty_info; } ;

/* Variables and functions */
 struct dirty_seglist_info* DIRTY_I (struct f2fs_sb_info*) ; 
 int NR_DIRTY_TYPE ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_victim_secmap (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  discard_dirty_segmap (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  kvfree (struct dirty_seglist_info*) ; 

__attribute__((used)) static void destroy_dirty_segmap(struct f2fs_sb_info *sbi)
{
	struct dirty_seglist_info *dirty_i = DIRTY_I(sbi);
	int i;

	if (!dirty_i)
		return;

	/* discard pre-free/dirty segments list */
	for (i = 0; i < NR_DIRTY_TYPE; i++)
		discard_dirty_segmap(sbi, i);

	destroy_victim_secmap(sbi);
	SM_I(sbi)->dirty_info = NULL;
	kvfree(dirty_i);
}
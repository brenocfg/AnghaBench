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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ subfolders; } ;

/* Variables and functions */
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFSPLUS_SB_HFSX ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfsplus_subfolders_dec(struct inode *dir)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);

	if (test_bit(HFSPLUS_SB_HFSX, &sbi->flags)) {
		/*
		 * Decrement subfolder count. Note, the value is only meaningful
		 * for folders with HFSPLUS_HAS_FOLDER_COUNT flag set.
		 *
		 * Check for zero. Some subfolders may have been created
		 * by an implementation ignorant of this counter.
		 */
		if (HFSPLUS_I(dir)->subfolders)
			HFSPLUS_I(dir)->subfolders--;
	}
}
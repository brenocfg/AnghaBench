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
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void verify_blkaddr(struct f2fs_sb_info *sbi,
					block_t blkaddr, int type)
{
	if (!f2fs_is_valid_blkaddr(sbi, blkaddr, type)) {
		f2fs_msg(sbi->sb, KERN_ERR,
			"invalid blkaddr: %u, type: %d, run fsck to fix.",
			blkaddr, type);
		f2fs_bug_on(sbi, 1);
	}
}
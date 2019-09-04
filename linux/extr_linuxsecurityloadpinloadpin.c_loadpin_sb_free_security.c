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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct super_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct super_block*) ; 
 struct super_block* pinned_root ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void loadpin_sb_free_security(struct super_block *mnt_sb)
{
	/*
	 * When unmounting the filesystem we were using for load
	 * pinning, we acknowledge the superblock release, but make sure
	 * no other modules or firmware can be loaded.
	 */
	if (!IS_ERR_OR_NULL(pinned_root) && mnt_sb == pinned_root) {
		pinned_root = ERR_PTR(-EIO);
		pr_info("umount pinned fs: refusing further loads\n");
	}
}
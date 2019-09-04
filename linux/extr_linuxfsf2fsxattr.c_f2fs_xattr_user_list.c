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
struct f2fs_sb_info {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool f2fs_xattr_user_list(struct dentry *dentry)
{
	struct f2fs_sb_info *sbi = F2FS_SB(dentry->d_sb);

	return test_opt(sbi, XATTR_USER);
}
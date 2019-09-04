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
struct erofs_sb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void default_options(struct erofs_sb_info *sbi)
{
#ifdef CONFIG_EROFS_FS_XATTR
	set_opt(sbi, XATTR_USER);
#endif

#ifdef CONFIG_EROFS_FS_POSIX_ACL
	set_opt(sbi, POSIX_ACL);
#endif
}
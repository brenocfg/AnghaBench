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
struct erofs_sb_info {int max_sync_decompress_pages; int /*<<< orphan*/  cache_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EROFS_ZIP_CACHE_READAROUND ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int /*<<< orphan*/  set_opt (struct erofs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void erofs_default_options(struct erofs_sb_info *sbi)
{
#ifdef CONFIG_EROFS_FS_ZIP
	sbi->cache_strategy = EROFS_ZIP_CACHE_READAROUND;
	sbi->max_sync_decompress_pages = 3;
#endif
#ifdef CONFIG_EROFS_FS_XATTR
	set_opt(sbi, XATTR_USER);
#endif
#ifdef CONFIG_EROFS_FS_POSIX_ACL
	set_opt(sbi, POSIX_ACL);
#endif
}
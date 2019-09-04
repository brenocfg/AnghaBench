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
typedef  int /*<<< orphan*/  erofs_blk_t ;

/* Variables and functions */

__attribute__((used)) static inline erofs_blk_t
xattrblock_addr(struct erofs_sb_info *sbi, unsigned xattr_id)
{
#ifdef CONFIG_EROFS_FS_XATTR
	return sbi->xattr_blkaddr +
		xattr_id * sizeof(__u32) / EROFS_BLKSIZ;
#else
	return 0;
#endif
}
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
struct super_block {TYPE_1__* s_bdev; } ;
struct f2fs_sb_info {struct super_block* sb; } ;
struct f2fs_attr {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_part; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ f2fs_sb_has_blkzoned (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_encrypt (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_extra_attr (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_flexible_inline_xattr (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_inode_chksum (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_inode_crtime (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_lost_found (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_project_quota (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_quota_ino (struct super_block*) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 

__attribute__((used)) static ssize_t features_show(struct f2fs_attr *a,
		struct f2fs_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->sb;
	int len = 0;

	if (!sb->s_bdev->bd_part)
		return snprintf(buf, PAGE_SIZE, "0\n");

	if (f2fs_sb_has_encrypt(sb))
		len += snprintf(buf, PAGE_SIZE - len, "%s",
						"encryption");
	if (f2fs_sb_has_blkzoned(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "blkzoned");
	if (f2fs_sb_has_extra_attr(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "extra_attr");
	if (f2fs_sb_has_project_quota(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "projquota");
	if (f2fs_sb_has_inode_chksum(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_checksum");
	if (f2fs_sb_has_flexible_inline_xattr(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "flexible_inline_xattr");
	if (f2fs_sb_has_quota_ino(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "quota_ino");
	if (f2fs_sb_has_inode_crtime(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_crtime");
	if (f2fs_sb_has_lost_found(sb))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "lost_found");
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");
	return len;
}
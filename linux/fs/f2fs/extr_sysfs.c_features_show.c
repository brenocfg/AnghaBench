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
 scalar_t__ f2fs_sb_has_blkzoned (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_casefold (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_encrypt (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_extra_attr (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_flexible_inline_xattr (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_inode_chksum (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_inode_crtime (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_lost_found (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_project_quota (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_quota_ino (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_sb_chksum (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_verity (struct f2fs_sb_info*) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 

__attribute__((used)) static ssize_t features_show(struct f2fs_attr *a,
		struct f2fs_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->sb;
	int len = 0;

	if (!sb->s_bdev->bd_part)
		return snprintf(buf, PAGE_SIZE, "0\n");

	if (f2fs_sb_has_encrypt(sbi))
		len += snprintf(buf, PAGE_SIZE - len, "%s",
						"encryption");
	if (f2fs_sb_has_blkzoned(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "blkzoned");
	if (f2fs_sb_has_extra_attr(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "extra_attr");
	if (f2fs_sb_has_project_quota(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "projquota");
	if (f2fs_sb_has_inode_chksum(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_checksum");
	if (f2fs_sb_has_flexible_inline_xattr(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "flexible_inline_xattr");
	if (f2fs_sb_has_quota_ino(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "quota_ino");
	if (f2fs_sb_has_inode_crtime(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "inode_crtime");
	if (f2fs_sb_has_lost_found(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "lost_found");
	if (f2fs_sb_has_verity(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "verity");
	if (f2fs_sb_has_sb_chksum(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "sb_checksum");
	if (f2fs_sb_has_casefold(sbi))
		len += snprintf(buf + len, PAGE_SIZE - len, "%s%s",
				len ? ", " : "", "casefold");
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");
	return len;
}
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
struct f2fs_attr {int id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  FEAT_ATOMIC_WRITE 140 
#define  FEAT_BLKZONED 139 
#define  FEAT_CASEFOLD 138 
#define  FEAT_CRYPTO 137 
#define  FEAT_EXTRA_ATTR 136 
#define  FEAT_FLEXIBLE_INLINE_XATTR 135 
#define  FEAT_INODE_CHECKSUM 134 
#define  FEAT_INODE_CRTIME 133 
#define  FEAT_LOST_FOUND 132 
#define  FEAT_PROJECT_QUOTA 131 
#define  FEAT_QUOTA_INO 130 
#define  FEAT_SB_CHECKSUM 129 
#define  FEAT_VERITY 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t f2fs_feature_show(struct f2fs_attr *a,
		struct f2fs_sb_info *sbi, char *buf)
{
	switch (a->id) {
	case FEAT_CRYPTO:
	case FEAT_BLKZONED:
	case FEAT_ATOMIC_WRITE:
	case FEAT_EXTRA_ATTR:
	case FEAT_PROJECT_QUOTA:
	case FEAT_INODE_CHECKSUM:
	case FEAT_FLEXIBLE_INLINE_XATTR:
	case FEAT_QUOTA_INO:
	case FEAT_INODE_CRTIME:
	case FEAT_LOST_FOUND:
	case FEAT_VERITY:
	case FEAT_SB_CHECKSUM:
	case FEAT_CASEFOLD:
		return snprintf(buf, PAGE_SIZE, "supported\n");
	}
	return 0;
}
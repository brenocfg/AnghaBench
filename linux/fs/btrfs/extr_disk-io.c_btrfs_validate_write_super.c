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
struct btrfs_super_block {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_CSUM_TYPE_CRC32 ; 
 int BTRFS_FEATURE_INCOMPAT_SUPP ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,...) ; 
 int /*<<< orphan*/  btrfs_super_csum_type (struct btrfs_super_block*) ; 
 int btrfs_super_incompat_flags (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_supported_super_csum (int /*<<< orphan*/ ) ; 
 int validate_super (struct btrfs_fs_info*,struct btrfs_super_block*,int) ; 

__attribute__((used)) static int btrfs_validate_write_super(struct btrfs_fs_info *fs_info,
				      struct btrfs_super_block *sb)
{
	int ret;

	ret = validate_super(fs_info, sb, -1);
	if (ret < 0)
		goto out;
	if (!btrfs_supported_super_csum(btrfs_super_csum_type(sb))) {
		ret = -EUCLEAN;
		btrfs_err(fs_info, "invalid csum type, has %u want %u",
			  btrfs_super_csum_type(sb), BTRFS_CSUM_TYPE_CRC32);
		goto out;
	}
	if (btrfs_super_incompat_flags(sb) & ~BTRFS_FEATURE_INCOMPAT_SUPP) {
		ret = -EUCLEAN;
		btrfs_err(fs_info,
		"invalid incompat flags, has 0x%llx valid mask 0x%llx",
			  btrfs_super_incompat_flags(sb),
			  (unsigned long long)BTRFS_FEATURE_INCOMPAT_SUPP);
		goto out;
	}
out:
	if (ret < 0)
		btrfs_err(fs_info,
		"super block corruption detected before writing it to disk");
	return ret;
}
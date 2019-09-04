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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct btrfs_super_block {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  crc ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BTRFS_CSUM_SIZE ; 
 scalar_t__ BTRFS_CSUM_TYPE_CRC32 ; 
 int BTRFS_SUPER_INFO_SIZE ; 
 int /*<<< orphan*/  btrfs_csum_data (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_csum_final (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btrfs_csum_sizes ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__) ; 
 scalar_t__ btrfs_super_csum_type (struct btrfs_super_block*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static int btrfs_check_super_csum(struct btrfs_fs_info *fs_info,
				  char *raw_disk_sb)
{
	struct btrfs_super_block *disk_sb =
		(struct btrfs_super_block *)raw_disk_sb;
	u16 csum_type = btrfs_super_csum_type(disk_sb);
	int ret = 0;

	if (csum_type == BTRFS_CSUM_TYPE_CRC32) {
		u32 crc = ~(u32)0;
		char result[sizeof(crc)];

		/*
		 * The super_block structure does not span the whole
		 * BTRFS_SUPER_INFO_SIZE range, we expect that the unused space
		 * is filled with zeros and is included in the checksum.
		 */
		crc = btrfs_csum_data(raw_disk_sb + BTRFS_CSUM_SIZE,
				crc, BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE);
		btrfs_csum_final(crc, result);

		if (memcmp(raw_disk_sb, result, sizeof(result)))
			ret = 1;
	}

	if (csum_type >= ARRAY_SIZE(btrfs_csum_sizes)) {
		btrfs_err(fs_info, "unsupported checksum algorithm %u",
				csum_type);
		ret = 1;
	}

	return ret;
}
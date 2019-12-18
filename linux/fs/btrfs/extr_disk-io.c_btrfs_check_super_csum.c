#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct btrfs_super_block {int /*<<< orphan*/  csum; } ;
struct btrfs_fs_info {int /*<<< orphan*/  csum_shash; } ;
struct TYPE_6__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int BTRFS_CSUM_SIZE ; 
 int BTRFS_SUPER_INFO_SIZE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_super_csum_size (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  crypto_shash_final (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  crypto_shash_init (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_shash_update (TYPE_1__*,char*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int btrfs_check_super_csum(struct btrfs_fs_info *fs_info,
				  char *raw_disk_sb)
{
	struct btrfs_super_block *disk_sb =
		(struct btrfs_super_block *)raw_disk_sb;
	char result[BTRFS_CSUM_SIZE];
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);

	/*
	 * The super_block structure does not span the whole
	 * BTRFS_SUPER_INFO_SIZE range, we expect that the unused space is
	 * filled with zeros and is included in the checksum.
	 */
	crypto_shash_update(shash, raw_disk_sb + BTRFS_CSUM_SIZE,
			    BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE);
	crypto_shash_final(shash, result);

	if (memcmp(disk_sb->csum, result, btrfs_super_csum_size(disk_sb)))
		return 1;

	return 0;
}
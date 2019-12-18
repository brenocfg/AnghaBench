#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int fsid; } ;
struct btrfs_super_block {TYPE_2__ dev_item; int /*<<< orphan*/  __unused_leafsize; } ;
struct btrfs_fs_info {TYPE_1__* fs_devices; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfs_chunk {int dummy; } ;
struct TYPE_3__ {int metadata_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 scalar_t__ BTRFS_MAGIC ; 
 int BTRFS_MAX_LEVEL ; 
 int BTRFS_MAX_METADATA_BLOCKSIZE ; 
 int BTRFS_SUPER_FLAG_SUPP ; 
 int BTRFS_SUPER_INFO_OFFSET ; 
 int BTRFS_SYSTEM_CHUNK_ARRAY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,...) ; 
 int btrfs_sb_offset (int) ; 
 int btrfs_super_bytenr (struct btrfs_super_block*) ; 
 int btrfs_super_bytes_used (struct btrfs_super_block*) ; 
 int btrfs_super_cache_generation (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_super_chunk_root (struct btrfs_super_block*) ; 
 int btrfs_super_chunk_root_generation (struct btrfs_super_block*) ; 
 int btrfs_super_chunk_root_level (struct btrfs_super_block*) ; 
 int btrfs_super_flags (struct btrfs_super_block*) ; 
 int btrfs_super_generation (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_super_log_root (struct btrfs_super_block*) ; 
 int btrfs_super_log_root_level (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_magic (struct btrfs_super_block*) ; 
 int btrfs_super_nodesize (struct btrfs_super_block*) ; 
 unsigned long btrfs_super_num_devices (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_super_root (struct btrfs_super_block*) ; 
 int btrfs_super_root_level (struct btrfs_super_block*) ; 
 int btrfs_super_sectorsize (struct btrfs_super_block*) ; 
 int btrfs_super_stripesize (struct btrfs_super_block*) ; 
 int btrfs_super_sys_array_size (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,int,...) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_super(struct btrfs_fs_info *fs_info,
			    struct btrfs_super_block *sb, int mirror_num)
{
	u64 nodesize = btrfs_super_nodesize(sb);
	u64 sectorsize = btrfs_super_sectorsize(sb);
	int ret = 0;

	if (btrfs_super_magic(sb) != BTRFS_MAGIC) {
		btrfs_err(fs_info, "no valid FS found");
		ret = -EINVAL;
	}
	if (btrfs_super_flags(sb) & ~BTRFS_SUPER_FLAG_SUPP) {
		btrfs_err(fs_info, "unrecognized or unsupported super flag: %llu",
				btrfs_super_flags(sb) & ~BTRFS_SUPER_FLAG_SUPP);
		ret = -EINVAL;
	}
	if (btrfs_super_root_level(sb) >= BTRFS_MAX_LEVEL) {
		btrfs_err(fs_info, "tree_root level too big: %d >= %d",
				btrfs_super_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	}
	if (btrfs_super_chunk_root_level(sb) >= BTRFS_MAX_LEVEL) {
		btrfs_err(fs_info, "chunk_root level too big: %d >= %d",
				btrfs_super_chunk_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	}
	if (btrfs_super_log_root_level(sb) >= BTRFS_MAX_LEVEL) {
		btrfs_err(fs_info, "log_root level too big: %d >= %d",
				btrfs_super_log_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	}

	/*
	 * Check sectorsize and nodesize first, other check will need it.
	 * Check all possible sectorsize(4K, 8K, 16K, 32K, 64K) here.
	 */
	if (!is_power_of_2(sectorsize) || sectorsize < 4096 ||
	    sectorsize > BTRFS_MAX_METADATA_BLOCKSIZE) {
		btrfs_err(fs_info, "invalid sectorsize %llu", sectorsize);
		ret = -EINVAL;
	}
	/* Only PAGE SIZE is supported yet */
	if (sectorsize != PAGE_SIZE) {
		btrfs_err(fs_info,
			"sectorsize %llu not supported yet, only support %lu",
			sectorsize, PAGE_SIZE);
		ret = -EINVAL;
	}
	if (!is_power_of_2(nodesize) || nodesize < sectorsize ||
	    nodesize > BTRFS_MAX_METADATA_BLOCKSIZE) {
		btrfs_err(fs_info, "invalid nodesize %llu", nodesize);
		ret = -EINVAL;
	}
	if (nodesize != le32_to_cpu(sb->__unused_leafsize)) {
		btrfs_err(fs_info, "invalid leafsize %u, should be %llu",
			  le32_to_cpu(sb->__unused_leafsize), nodesize);
		ret = -EINVAL;
	}

	/* Root alignment check */
	if (!IS_ALIGNED(btrfs_super_root(sb), sectorsize)) {
		btrfs_warn(fs_info, "tree_root block unaligned: %llu",
			   btrfs_super_root(sb));
		ret = -EINVAL;
	}
	if (!IS_ALIGNED(btrfs_super_chunk_root(sb), sectorsize)) {
		btrfs_warn(fs_info, "chunk_root block unaligned: %llu",
			   btrfs_super_chunk_root(sb));
		ret = -EINVAL;
	}
	if (!IS_ALIGNED(btrfs_super_log_root(sb), sectorsize)) {
		btrfs_warn(fs_info, "log_root block unaligned: %llu",
			   btrfs_super_log_root(sb));
		ret = -EINVAL;
	}

	if (memcmp(fs_info->fs_devices->metadata_uuid, sb->dev_item.fsid,
		   BTRFS_FSID_SIZE) != 0) {
		btrfs_err(fs_info,
			"dev_item UUID does not match metadata fsid: %pU != %pU",
			fs_info->fs_devices->metadata_uuid, sb->dev_item.fsid);
		ret = -EINVAL;
	}

	/*
	 * Hint to catch really bogus numbers, bitflips or so, more exact checks are
	 * done later
	 */
	if (btrfs_super_bytes_used(sb) < 6 * btrfs_super_nodesize(sb)) {
		btrfs_err(fs_info, "bytes_used is too small %llu",
			  btrfs_super_bytes_used(sb));
		ret = -EINVAL;
	}
	if (!is_power_of_2(btrfs_super_stripesize(sb))) {
		btrfs_err(fs_info, "invalid stripesize %u",
			  btrfs_super_stripesize(sb));
		ret = -EINVAL;
	}
	if (btrfs_super_num_devices(sb) > (1UL << 31))
		btrfs_warn(fs_info, "suspicious number of devices: %llu",
			   btrfs_super_num_devices(sb));
	if (btrfs_super_num_devices(sb) == 0) {
		btrfs_err(fs_info, "number of devices is 0");
		ret = -EINVAL;
	}

	if (mirror_num >= 0 &&
	    btrfs_super_bytenr(sb) != btrfs_sb_offset(mirror_num)) {
		btrfs_err(fs_info, "super offset mismatch %llu != %u",
			  btrfs_super_bytenr(sb), BTRFS_SUPER_INFO_OFFSET);
		ret = -EINVAL;
	}

	/*
	 * Obvious sys_chunk_array corruptions, it must hold at least one key
	 * and one chunk
	 */
	if (btrfs_super_sys_array_size(sb) > BTRFS_SYSTEM_CHUNK_ARRAY_SIZE) {
		btrfs_err(fs_info, "system chunk array too big %u > %u",
			  btrfs_super_sys_array_size(sb),
			  BTRFS_SYSTEM_CHUNK_ARRAY_SIZE);
		ret = -EINVAL;
	}
	if (btrfs_super_sys_array_size(sb) < sizeof(struct btrfs_disk_key)
			+ sizeof(struct btrfs_chunk)) {
		btrfs_err(fs_info, "system chunk array too small %u < %zu",
			  btrfs_super_sys_array_size(sb),
			  sizeof(struct btrfs_disk_key)
			  + sizeof(struct btrfs_chunk));
		ret = -EINVAL;
	}

	/*
	 * The generation is a global counter, we'll trust it more than the others
	 * but it's still possible that it's the one that's wrong.
	 */
	if (btrfs_super_generation(sb) < btrfs_super_chunk_root_generation(sb))
		btrfs_warn(fs_info,
			"suspicious: generation < chunk_root_generation: %llu < %llu",
			btrfs_super_generation(sb),
			btrfs_super_chunk_root_generation(sb));
	if (btrfs_super_generation(sb) < btrfs_super_cache_generation(sb)
	    && btrfs_super_cache_generation(sb) != (u64)-1)
		btrfs_warn(fs_info,
			"suspicious: generation < cache_generation: %llu < %llu",
			btrfs_super_generation(sb),
			btrfs_super_cache_generation(sb));

	return ret;
}
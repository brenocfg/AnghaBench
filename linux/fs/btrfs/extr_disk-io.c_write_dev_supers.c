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
typedef  int u64 ;
struct buffer_head {struct btrfs_device* b_private; int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_data; } ;
struct btrfs_super_block {int /*<<< orphan*/  csum; } ;
struct btrfs_fs_info {int /*<<< orphan*/  csum_shash; } ;
struct btrfs_device {scalar_t__ commit_total_bytes; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int BTRFS_BDEV_BLOCKSIZE ; 
 int BTRFS_CSUM_SIZE ; 
 scalar_t__ BTRFS_SUPER_INFO_SIZE ; 
 int BTRFS_SUPER_MIRROR_MAX ; 
 int /*<<< orphan*/  NOBARRIER ; 
 int REQ_FUA ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PRIO ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct buffer_head* __getblk (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_end_buffer_write_sync ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int) ; 
 int btrfs_sb_offset (int) ; 
 int /*<<< orphan*/  btrfs_set_super_bytenr (struct btrfs_super_block*,int) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfsic_submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 int /*<<< orphan*/  crypto_shash_final (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_init (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_shash_update (TYPE_1__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct btrfs_super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int write_dev_supers(struct btrfs_device *device,
			    struct btrfs_super_block *sb, int max_mirrors)
{
	struct btrfs_fs_info *fs_info = device->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	struct buffer_head *bh;
	int i;
	int ret;
	int errors = 0;
	u64 bytenr;
	int op_flags;

	if (max_mirrors == 0)
		max_mirrors = BTRFS_SUPER_MIRROR_MAX;

	shash->tfm = fs_info->csum_shash;

	for (i = 0; i < max_mirrors; i++) {
		bytenr = btrfs_sb_offset(i);
		if (bytenr + BTRFS_SUPER_INFO_SIZE >=
		    device->commit_total_bytes)
			break;

		btrfs_set_super_bytenr(sb, bytenr);

		crypto_shash_init(shash);
		crypto_shash_update(shash, (const char *)sb + BTRFS_CSUM_SIZE,
				    BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE);
		crypto_shash_final(shash, sb->csum);

		/* One reference for us, and we leave it for the caller */
		bh = __getblk(device->bdev, bytenr / BTRFS_BDEV_BLOCKSIZE,
			      BTRFS_SUPER_INFO_SIZE);
		if (!bh) {
			btrfs_err(device->fs_info,
			    "couldn't get super buffer head for bytenr %llu",
			    bytenr);
			errors++;
			continue;
		}

		memcpy(bh->b_data, sb, BTRFS_SUPER_INFO_SIZE);

		/* one reference for submit_bh */
		get_bh(bh);

		set_buffer_uptodate(bh);
		lock_buffer(bh);
		bh->b_end_io = btrfs_end_buffer_write_sync;
		bh->b_private = device;

		/*
		 * we fua the first super.  The others we allow
		 * to go down lazy.
		 */
		op_flags = REQ_SYNC | REQ_META | REQ_PRIO;
		if (i == 0 && !btrfs_test_opt(device->fs_info, NOBARRIER))
			op_flags |= REQ_FUA;
		ret = btrfsic_submit_bh(REQ_OP_WRITE, op_flags, bh);
		if (ret)
			errors++;
	}
	return errors < i ? 0 : -1;
}
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
typedef  scalar_t__ u64 ;
struct btrfsic_state {int /*<<< orphan*/  metablock_size; struct btrfs_fs_info* fs_info; } ;
struct btrfsic_dev_state {scalar_t__ bdev; int /*<<< orphan*/  name; } ;
struct btrfsic_block_data_ctx {scalar_t__ dev_bytenr; TYPE_1__* dev; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ bdev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int btrfs_num_copies (struct btrfs_fs_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int btrfsic_map_block (struct btrfsic_state*,scalar_t__,int /*<<< orphan*/ ,struct btrfsic_block_data_ctx*,int) ; 
 int /*<<< orphan*/  btrfsic_release_block_ctx (struct btrfsic_block_data_ctx*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,int,...) ; 

__attribute__((used)) static void btrfsic_cmp_log_and_dev_bytenr(struct btrfsic_state *state,
					   u64 bytenr,
					   struct btrfsic_dev_state *dev_state,
					   u64 dev_bytenr)
{
	struct btrfs_fs_info *fs_info = state->fs_info;
	struct btrfsic_block_data_ctx block_ctx;
	int num_copies;
	int mirror_num;
	int match = 0;
	int ret;

	num_copies = btrfs_num_copies(fs_info, bytenr, state->metablock_size);

	for (mirror_num = 1; mirror_num <= num_copies; mirror_num++) {
		ret = btrfsic_map_block(state, bytenr, state->metablock_size,
					&block_ctx, mirror_num);
		if (ret) {
			pr_info("btrfsic: btrfsic_map_block(logical @%llu, mirror %d) failed!\n",
			       bytenr, mirror_num);
			continue;
		}

		if (dev_state->bdev == block_ctx.dev->bdev &&
		    dev_bytenr == block_ctx.dev_bytenr) {
			match++;
			btrfsic_release_block_ctx(&block_ctx);
			break;
		}
		btrfsic_release_block_ctx(&block_ctx);
	}

	if (WARN_ON(!match)) {
		pr_info("btrfs: attempt to write M-block which contains logical bytenr that doesn't map to dev+physical bytenr of submit_bio, buffer->log_bytenr=%llu, submit_bio(bdev=%s, phys_bytenr=%llu)!\n",
		       bytenr, dev_state->name, dev_bytenr);
		for (mirror_num = 1; mirror_num <= num_copies; mirror_num++) {
			ret = btrfsic_map_block(state, bytenr,
						state->metablock_size,
						&block_ctx, mirror_num);
			if (ret)
				continue;

			pr_info("Read logical bytenr @%llu maps to (%s/%llu/%d)\n",
			       bytenr, block_ctx.dev->name,
			       block_ctx.dev_bytenr, mirror_num);
		}
	}
}
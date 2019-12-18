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
typedef  scalar_t__ u64 ;
struct scrub_parity {int logic_start; int /*<<< orphan*/  nsectors; int /*<<< orphan*/  dbitmap; int /*<<< orphan*/  ebitmap; int /*<<< orphan*/  scrub_dev; scalar_t__ logic_end; struct scrub_ctx* sctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  malloc_errors; } ;
struct scrub_ctx {int /*<<< orphan*/  stat_lock; TYPE_2__ stat; struct btrfs_fs_info* fs_info; } ;
struct btrfs_raid_bio {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_bio {int /*<<< orphan*/  raid_map; } ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct scrub_parity* bi_private; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_MAP_WRITE ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_bio_counter_dec (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_bio_counter_inc_blocked (struct btrfs_fs_info*) ; 
 struct bio* btrfs_io_bio_alloc (int /*<<< orphan*/ ) ; 
 int btrfs_map_sblock (struct btrfs_fs_info*,int /*<<< orphan*/ ,int,scalar_t__*,struct btrfs_bio**) ; 
 int /*<<< orphan*/  btrfs_put_bbio (struct btrfs_bio*) ; 
 struct btrfs_raid_bio* raid56_parity_alloc_scrub_rbio (struct btrfs_fs_info*,struct bio*,struct btrfs_bio*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid56_parity_submit_scrub_rbio (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  scrub_free_parity (struct scrub_parity*) ; 
 int /*<<< orphan*/  scrub_parity_bio_endio ; 
 int /*<<< orphan*/  scrub_pending_bio_inc (struct scrub_ctx*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrub_parity_check_and_repair(struct scrub_parity *sparity)
{
	struct scrub_ctx *sctx = sparity->sctx;
	struct btrfs_fs_info *fs_info = sctx->fs_info;
	struct bio *bio;
	struct btrfs_raid_bio *rbio;
	struct btrfs_bio *bbio = NULL;
	u64 length;
	int ret;

	if (!bitmap_andnot(sparity->dbitmap, sparity->dbitmap, sparity->ebitmap,
			   sparity->nsectors))
		goto out;

	length = sparity->logic_end - sparity->logic_start;

	btrfs_bio_counter_inc_blocked(fs_info);
	ret = btrfs_map_sblock(fs_info, BTRFS_MAP_WRITE, sparity->logic_start,
			       &length, &bbio);
	if (ret || !bbio || !bbio->raid_map)
		goto bbio_out;

	bio = btrfs_io_bio_alloc(0);
	bio->bi_iter.bi_sector = sparity->logic_start >> 9;
	bio->bi_private = sparity;
	bio->bi_end_io = scrub_parity_bio_endio;

	rbio = raid56_parity_alloc_scrub_rbio(fs_info, bio, bbio,
					      length, sparity->scrub_dev,
					      sparity->dbitmap,
					      sparity->nsectors);
	if (!rbio)
		goto rbio_out;

	scrub_pending_bio_inc(sctx);
	raid56_parity_submit_scrub_rbio(rbio);
	return;

rbio_out:
	bio_put(bio);
bbio_out:
	btrfs_bio_counter_dec(fs_info);
	btrfs_put_bbio(bbio);
	bitmap_or(sparity->ebitmap, sparity->ebitmap, sparity->dbitmap,
		  sparity->nsectors);
	spin_lock(&sctx->stat_lock);
	sctx->stat.malloc_errors++;
	spin_unlock(&sctx->stat_lock);
out:
	scrub_free_parity(sparity);
}
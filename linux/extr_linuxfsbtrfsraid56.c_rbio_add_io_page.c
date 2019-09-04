#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {int dummy; } ;
struct btrfs_raid_bio {TYPE_1__* bbio; } ;
struct btrfs_bio_stripe {int physical; TYPE_2__* dev; } ;
struct bio_list {struct bio* tail; } ;
struct TYPE_7__ {int bi_sector; scalar_t__ bi_size; } ;
struct bio {scalar_t__ bi_disk; scalar_t__ bi_partno; TYPE_3__ bi_iter; int /*<<< orphan*/  bi_status; } ;
struct TYPE_8__ {scalar_t__ bd_disk; scalar_t__ bd_partno; } ;
struct TYPE_6__ {TYPE_4__* bdev; } ;
struct TYPE_5__ {struct btrfs_bio_stripe* stripes; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,TYPE_4__*) ; 
 struct bio* btrfs_io_bio_alloc (int) ; 
 int fail_rbio_index (struct btrfs_raid_bio*,int) ; 

__attribute__((used)) static int rbio_add_io_page(struct btrfs_raid_bio *rbio,
			    struct bio_list *bio_list,
			    struct page *page,
			    int stripe_nr,
			    unsigned long page_index,
			    unsigned long bio_max_len)
{
	struct bio *last = bio_list->tail;
	u64 last_end = 0;
	int ret;
	struct bio *bio;
	struct btrfs_bio_stripe *stripe;
	u64 disk_start;

	stripe = &rbio->bbio->stripes[stripe_nr];
	disk_start = stripe->physical + (page_index << PAGE_SHIFT);

	/* if the device is missing, just fail this stripe */
	if (!stripe->dev->bdev)
		return fail_rbio_index(rbio, stripe_nr);

	/* see if we can add this page onto our existing bio */
	if (last) {
		last_end = (u64)last->bi_iter.bi_sector << 9;
		last_end += last->bi_iter.bi_size;

		/*
		 * we can't merge these if they are from different
		 * devices or if they are not contiguous
		 */
		if (last_end == disk_start && stripe->dev->bdev &&
		    !last->bi_status &&
		    last->bi_disk == stripe->dev->bdev->bd_disk &&
		    last->bi_partno == stripe->dev->bdev->bd_partno) {
			ret = bio_add_page(last, page, PAGE_SIZE, 0);
			if (ret == PAGE_SIZE)
				return 0;
		}
	}

	/* put a new bio on the list */
	bio = btrfs_io_bio_alloc(bio_max_len >> PAGE_SHIFT ?: 1);
	bio->bi_iter.bi_size = 0;
	bio_set_dev(bio, stripe->dev->bdev);
	bio->bi_iter.bi_sector = disk_start >> 9;

	bio_add_page(bio, page, PAGE_SIZE, 0);
	bio_list_add(bio_list, bio);
	return 0;
}
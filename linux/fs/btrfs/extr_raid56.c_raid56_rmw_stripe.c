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
struct page {int dummy; } ;
struct btrfs_raid_bio {int nr_data; int stripe_npages; int /*<<< orphan*/  fs_info; int /*<<< orphan*/  stripes_pending; int /*<<< orphan*/  stripe_len; int /*<<< orphan*/  error; } ;
struct bio_list {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_opf; int /*<<< orphan*/  bi_end_io; struct btrfs_raid_bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BTRFS_WQ_ENDIO_RAID56 ; 
 int EIO ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int alloc_rbio_pages (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int bio_list_size (struct bio_list*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  btrfs_bio_wq_end_io (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rbio_pages (struct btrfs_raid_bio*) ; 
 struct page* page_in_rbio (struct btrfs_raid_bio*,int,int,int) ; 
 int /*<<< orphan*/  raid_rmw_end_io ; 
 int rbio_add_io_page (struct btrfs_raid_bio*,struct bio_list*,struct page*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbio_orig_end_io (struct btrfs_raid_bio*,int /*<<< orphan*/ ) ; 
 struct page* rbio_stripe_page (struct btrfs_raid_bio*,int,int) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  validate_rbio_for_rmw (struct btrfs_raid_bio*) ; 

__attribute__((used)) static int raid56_rmw_stripe(struct btrfs_raid_bio *rbio)
{
	int bios_to_read = 0;
	struct bio_list bio_list;
	int ret;
	int pagenr;
	int stripe;
	struct bio *bio;

	bio_list_init(&bio_list);

	ret = alloc_rbio_pages(rbio);
	if (ret)
		goto cleanup;

	index_rbio_pages(rbio);

	atomic_set(&rbio->error, 0);
	/*
	 * build a list of bios to read all the missing parts of this
	 * stripe
	 */
	for (stripe = 0; stripe < rbio->nr_data; stripe++) {
		for (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) {
			struct page *page;
			/*
			 * we want to find all the pages missing from
			 * the rbio and read them from the disk.  If
			 * page_in_rbio finds a page in the bio list
			 * we don't need to read it off the stripe.
			 */
			page = page_in_rbio(rbio, stripe, pagenr, 1);
			if (page)
				continue;

			page = rbio_stripe_page(rbio, stripe, pagenr);
			/*
			 * the bio cache may have handed us an uptodate
			 * page.  If so, be happy and use it
			 */
			if (PageUptodate(page))
				continue;

			ret = rbio_add_io_page(rbio, &bio_list, page,
				       stripe, pagenr, rbio->stripe_len);
			if (ret)
				goto cleanup;
		}
	}

	bios_to_read = bio_list_size(&bio_list);
	if (!bios_to_read) {
		/*
		 * this can happen if others have merged with
		 * us, it means there is nothing left to read.
		 * But if there are missing devices it may not be
		 * safe to do the full stripe write yet.
		 */
		goto finish;
	}

	/*
	 * the bbio may be freed once we submit the last bio.  Make sure
	 * not to touch it after that
	 */
	atomic_set(&rbio->stripes_pending, bios_to_read);
	while (1) {
		bio = bio_list_pop(&bio_list);
		if (!bio)
			break;

		bio->bi_private = rbio;
		bio->bi_end_io = raid_rmw_end_io;
		bio->bi_opf = REQ_OP_READ;

		btrfs_bio_wq_end_io(rbio->fs_info, bio, BTRFS_WQ_ENDIO_RAID56);

		submit_bio(bio);
	}
	/* the actual write will happen once the reads are done */
	return 0;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);

	while ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);

	return -EIO;

finish:
	validate_rbio_for_rmw(rbio);
	return 0;
}
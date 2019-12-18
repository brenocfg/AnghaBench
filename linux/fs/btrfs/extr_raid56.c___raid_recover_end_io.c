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
struct page {int dummy; } ;
struct btrfs_raid_bio {int real_stripes; int faila; int failb; scalar_t__ operation; int stripe_npages; int nr_data; int /*<<< orphan*/  flags; TYPE_1__* bbio; int /*<<< orphan*/  dbitmap; int /*<<< orphan*/  bio_list_lock; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {int map_type; scalar_t__* raid_map; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 
 scalar_t__ BTRFS_RBIO_PARITY_SCRUB ; 
 scalar_t__ BTRFS_RBIO_READ_REBUILD ; 
 scalar_t__ BTRFS_RBIO_REBUILD_MISSING ; 
 scalar_t__ BTRFS_RBIO_WRITE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ RAID5_P_STRIPE ; 
 scalar_t__ RAID6_Q_STRIPE ; 
 int /*<<< orphan*/  RBIO_CACHE_READY_BIT ; 
 int /*<<< orphan*/  RBIO_RMW_LOCKED_BIT ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  cache_rbio_pages (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 int /*<<< orphan*/  finish_parity_scrub (struct btrfs_raid_bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_rmw (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  index_rbio_pages (struct btrfs_raid_bio*) ; 
 void** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 struct page* page_in_rbio (struct btrfs_raid_bio*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid6_2data_recov (int,int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  raid6_datap_recov (int,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  rbio_orig_end_io (struct btrfs_raid_bio*,scalar_t__) ; 
 struct page* rbio_stripe_page (struct btrfs_raid_bio*,int,int) ; 
 int /*<<< orphan*/  run_xor (void**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __raid_recover_end_io(struct btrfs_raid_bio *rbio)
{
	int pagenr, stripe;
	void **pointers;
	int faila = -1, failb = -1;
	struct page *page;
	blk_status_t err;
	int i;

	pointers = kcalloc(rbio->real_stripes, sizeof(void *), GFP_NOFS);
	if (!pointers) {
		err = BLK_STS_RESOURCE;
		goto cleanup_io;
	}

	faila = rbio->faila;
	failb = rbio->failb;

	if (rbio->operation == BTRFS_RBIO_READ_REBUILD ||
	    rbio->operation == BTRFS_RBIO_REBUILD_MISSING) {
		spin_lock_irq(&rbio->bio_list_lock);
		set_bit(RBIO_RMW_LOCKED_BIT, &rbio->flags);
		spin_unlock_irq(&rbio->bio_list_lock);
	}

	index_rbio_pages(rbio);

	for (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) {
		/*
		 * Now we just use bitmap to mark the horizontal stripes in
		 * which we have data when doing parity scrub.
		 */
		if (rbio->operation == BTRFS_RBIO_PARITY_SCRUB &&
		    !test_bit(pagenr, rbio->dbitmap))
			continue;

		/* setup our array of pointers with pages
		 * from each stripe
		 */
		for (stripe = 0; stripe < rbio->real_stripes; stripe++) {
			/*
			 * if we're rebuilding a read, we have to use
			 * pages from the bio list
			 */
			if ((rbio->operation == BTRFS_RBIO_READ_REBUILD ||
			     rbio->operation == BTRFS_RBIO_REBUILD_MISSING) &&
			    (stripe == faila || stripe == failb)) {
				page = page_in_rbio(rbio, stripe, pagenr, 0);
			} else {
				page = rbio_stripe_page(rbio, stripe, pagenr);
			}
			pointers[stripe] = kmap(page);
		}

		/* all raid6 handling here */
		if (rbio->bbio->map_type & BTRFS_BLOCK_GROUP_RAID6) {
			/*
			 * single failure, rebuild from parity raid5
			 * style
			 */
			if (failb < 0) {
				if (faila == rbio->nr_data) {
					/*
					 * Just the P stripe has failed, without
					 * a bad data or Q stripe.
					 * TODO, we should redo the xor here.
					 */
					err = BLK_STS_IOERR;
					goto cleanup;
				}
				/*
				 * a single failure in raid6 is rebuilt
				 * in the pstripe code below
				 */
				goto pstripe;
			}

			/* make sure our ps and qs are in order */
			if (faila > failb) {
				int tmp = failb;
				failb = faila;
				faila = tmp;
			}

			/* if the q stripe is failed, do a pstripe reconstruction
			 * from the xors.
			 * If both the q stripe and the P stripe are failed, we're
			 * here due to a crc mismatch and we can't give them the
			 * data they want
			 */
			if (rbio->bbio->raid_map[failb] == RAID6_Q_STRIPE) {
				if (rbio->bbio->raid_map[faila] ==
				    RAID5_P_STRIPE) {
					err = BLK_STS_IOERR;
					goto cleanup;
				}
				/*
				 * otherwise we have one bad data stripe and
				 * a good P stripe.  raid5!
				 */
				goto pstripe;
			}

			if (rbio->bbio->raid_map[failb] == RAID5_P_STRIPE) {
				raid6_datap_recov(rbio->real_stripes,
						  PAGE_SIZE, faila, pointers);
			} else {
				raid6_2data_recov(rbio->real_stripes,
						  PAGE_SIZE, faila, failb,
						  pointers);
			}
		} else {
			void *p;

			/* rebuild from P stripe here (raid5 or raid6) */
			BUG_ON(failb != -1);
pstripe:
			/* Copy parity block into failed block to start with */
			copy_page(pointers[faila], pointers[rbio->nr_data]);

			/* rearrange the pointer array */
			p = pointers[faila];
			for (stripe = faila; stripe < rbio->nr_data - 1; stripe++)
				pointers[stripe] = pointers[stripe + 1];
			pointers[rbio->nr_data - 1] = p;

			/* xor in the rest */
			run_xor(pointers, rbio->nr_data - 1, PAGE_SIZE);
		}
		/* if we're doing this rebuild as part of an rmw, go through
		 * and set all of our private rbio pages in the
		 * failed stripes as uptodate.  This way finish_rmw will
		 * know they can be trusted.  If this was a read reconstruction,
		 * other endio functions will fiddle the uptodate bits
		 */
		if (rbio->operation == BTRFS_RBIO_WRITE) {
			for (i = 0;  i < rbio->stripe_npages; i++) {
				if (faila != -1) {
					page = rbio_stripe_page(rbio, faila, i);
					SetPageUptodate(page);
				}
				if (failb != -1) {
					page = rbio_stripe_page(rbio, failb, i);
					SetPageUptodate(page);
				}
			}
		}
		for (stripe = 0; stripe < rbio->real_stripes; stripe++) {
			/*
			 * if we're rebuilding a read, we have to use
			 * pages from the bio list
			 */
			if ((rbio->operation == BTRFS_RBIO_READ_REBUILD ||
			     rbio->operation == BTRFS_RBIO_REBUILD_MISSING) &&
			    (stripe == faila || stripe == failb)) {
				page = page_in_rbio(rbio, stripe, pagenr, 0);
			} else {
				page = rbio_stripe_page(rbio, stripe, pagenr);
			}
			kunmap(page);
		}
	}

	err = BLK_STS_OK;
cleanup:
	kfree(pointers);

cleanup_io:
	/*
	 * Similar to READ_REBUILD, REBUILD_MISSING at this point also has a
	 * valid rbio which is consistent with ondisk content, thus such a
	 * valid rbio can be cached to avoid further disk reads.
	 */
	if (rbio->operation == BTRFS_RBIO_READ_REBUILD ||
	    rbio->operation == BTRFS_RBIO_REBUILD_MISSING) {
		/*
		 * - In case of two failures, where rbio->failb != -1:
		 *
		 *   Do not cache this rbio since the above read reconstruction
		 *   (raid6_datap_recov() or raid6_2data_recov()) may have
		 *   changed some content of stripes which are not identical to
		 *   on-disk content any more, otherwise, a later write/recover
		 *   may steal stripe_pages from this rbio and end up with
		 *   corruptions or rebuild failures.
		 *
		 * - In case of single failure, where rbio->failb == -1:
		 *
		 *   Cache this rbio iff the above read reconstruction is
		 *   executed without problems.
		 */
		if (err == BLK_STS_OK && rbio->failb < 0)
			cache_rbio_pages(rbio);
		else
			clear_bit(RBIO_CACHE_READY_BIT, &rbio->flags);

		rbio_orig_end_io(rbio, err);
	} else if (err == BLK_STS_OK) {
		rbio->faila = -1;
		rbio->failb = -1;

		if (rbio->operation == BTRFS_RBIO_WRITE)
			finish_rmw(rbio);
		else if (rbio->operation == BTRFS_RBIO_PARITY_SCRUB)
			finish_parity_scrub(rbio, 0);
		else
			BUG();
	} else {
		rbio_orig_end_io(rbio, err);
	}
}
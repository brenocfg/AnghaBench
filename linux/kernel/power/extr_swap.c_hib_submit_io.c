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
struct hib_bio_batch {int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {struct hib_bio_batch* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int EFAULT ; 
 int GFP_NOIO ; 
 int PAGE_SIZE ; 
 int __GFP_HIGH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int /*<<< orphan*/  hib_end_io ; 
 int /*<<< orphan*/  hib_resume_bdev ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long long) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int submit_bio_wait (struct bio*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static int hib_submit_io(int op, int op_flags, pgoff_t page_off, void *addr,
		struct hib_bio_batch *hb)
{
	struct page *page = virt_to_page(addr);
	struct bio *bio;
	int error = 0;

	bio = bio_alloc(GFP_NOIO | __GFP_HIGH, 1);
	bio->bi_iter.bi_sector = page_off * (PAGE_SIZE >> 9);
	bio_set_dev(bio, hib_resume_bdev);
	bio_set_op_attrs(bio, op, op_flags);

	if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) {
		pr_err("Adding page to bio failed at %llu\n",
		       (unsigned long long)bio->bi_iter.bi_sector);
		bio_put(bio);
		return -EFAULT;
	}

	if (hb) {
		bio->bi_end_io = hib_end_io;
		bio->bi_private = hb;
		atomic_inc(&hb->count);
		submit_bio(bio);
	} else {
		error = submit_bio_wait(bio);
		bio_put(bio);
	}

	return error;
}
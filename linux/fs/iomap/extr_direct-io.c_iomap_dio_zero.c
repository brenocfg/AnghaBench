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
struct iomap_dio {int dummy; } ;
struct iomap {int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct iomap_dio* bi_private; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int REQ_IDLE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bio_add_page (struct bio*,struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  iomap_dio_bio_end_io ; 
 int /*<<< orphan*/  iomap_dio_submit_bio (struct iomap_dio*,struct iomap*,struct bio*) ; 
 int /*<<< orphan*/  iomap_sector (struct iomap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iomap_dio_zero(struct iomap_dio *dio, struct iomap *iomap, loff_t pos,
		unsigned len)
{
	struct page *page = ZERO_PAGE(0);
	int flags = REQ_SYNC | REQ_IDLE;
	struct bio *bio;

	bio = bio_alloc(GFP_KERNEL, 1);
	bio_set_dev(bio, iomap->bdev);
	bio->bi_iter.bi_sector = iomap_sector(iomap, pos);
	bio->bi_private = dio;
	bio->bi_end_io = iomap_dio_bio_end_io;

	get_page(page);
	__bio_add_page(bio, page, len, 0);
	bio_set_op_attrs(bio, REQ_OP_WRITE, flags);
	iomap_dio_submit_bio(dio, iomap, bio);
}
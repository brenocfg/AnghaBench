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
struct parallel_io {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {struct parallel_io* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  bio_end_io_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int PF_MEMALLOC ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 TYPE_2__* current ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *
bl_alloc_init_bio(int npg, struct block_device *bdev, sector_t disk_sector,
		bio_end_io_t end_io, struct parallel_io *par)
{
	struct bio *bio;

	npg = min(npg, BIO_MAX_PAGES);
	bio = bio_alloc(GFP_NOIO, npg);
	if (!bio && (current->flags & PF_MEMALLOC)) {
		while (!bio && (npg /= 2))
			bio = bio_alloc(GFP_NOIO, npg);
	}

	if (bio) {
		bio->bi_iter.bi_sector = disk_sector;
		bio_set_dev(bio, bdev);
		bio->bi_end_io = end_io;
		bio->bi_private = par;
	}
	return bio;
}
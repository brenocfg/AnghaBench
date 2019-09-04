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
struct block_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PF_MEMALLOC ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 TYPE_2__* current ; 

__attribute__((used)) static struct bio *
mpage_alloc(struct block_device *bdev,
		sector_t first_sector, int nr_vecs,
		gfp_t gfp_flags)
{
	struct bio *bio;

	/* Restrict the given (page cache) mask for slab allocations */
	gfp_flags &= GFP_KERNEL;
	bio = bio_alloc(gfp_flags, nr_vecs);

	if (bio == NULL && (current->flags & PF_MEMALLOC)) {
		while (!bio && (nr_vecs /= 2))
			bio = bio_alloc(gfp_flags, nr_vecs);
	}

	if (bio) {
		bio_set_dev(bio, bdev);
		bio->bi_iter.bi_sector = first_sector;
	}
	return bio;
}
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
struct the_nilfs {int ns_blocksize_bits; int /*<<< orphan*/  ns_bdev; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct bio*) ; 

__attribute__((used)) static struct bio *nilfs_alloc_seg_bio(struct the_nilfs *nilfs, sector_t start,
				       int nr_vecs)
{
	struct bio *bio;

	bio = bio_alloc(GFP_NOIO, nr_vecs);
	if (bio == NULL) {
		while (!bio && (nr_vecs >>= 1))
			bio = bio_alloc(GFP_NOIO, nr_vecs);
	}
	if (likely(bio)) {
		bio_set_dev(bio, nilfs->ns_bdev);
		bio->bi_iter.bi_sector =
			start << (nilfs->ns_blocksize_bits - 9);
	}
	return bio;
}
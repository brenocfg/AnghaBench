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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/  bi_end_io; } ;
typedef  int gfp_t ;
typedef  int erofs_blk_t ;
typedef  int /*<<< orphan*/  bio_end_io_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 int LOG_SECTORS_PER_BLOCK ; 
 int PF_MEMALLOC ; 
 int __GFP_NOFAIL ; 
 struct bio* bio_alloc (int,unsigned int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct bio *prepare_bio(
	struct super_block *sb,
	erofs_blk_t blkaddr, unsigned nr_pages,
	bio_end_io_t endio)
{
	gfp_t gfp = GFP_NOIO;
	struct bio *bio = bio_alloc(gfp, nr_pages);

	if (unlikely(bio == NULL) &&
		(current->flags & PF_MEMALLOC)) {
		do {
			nr_pages /= 2;
			if (unlikely(!nr_pages)) {
				bio = bio_alloc(gfp | __GFP_NOFAIL, 1);
				BUG_ON(bio == NULL);
				break;
			}
			bio = bio_alloc(gfp, nr_pages);
		} while (bio == NULL);
	}

	bio->bi_end_io = endio;
	bio_set_dev(bio, sb->s_bdev);
	bio->bi_iter.bi_sector = blkaddr << LOG_SECTORS_PER_BLOCK;
	return bio;
}
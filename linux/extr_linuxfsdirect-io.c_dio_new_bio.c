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
struct dio_submit {int blkbits; scalar_t__ boundary; int /*<<< orphan*/  pages_in_io; } ;
struct dio {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_bdev; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dio_bio_alloc (struct dio*,struct dio_submit*,int /*<<< orphan*/ ,int,int) ; 
 int dio_bio_reap (struct dio*,struct dio_submit*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dio_new_bio(struct dio *dio, struct dio_submit *sdio,
		sector_t start_sector, struct buffer_head *map_bh)
{
	sector_t sector;
	int ret, nr_pages;

	ret = dio_bio_reap(dio, sdio);
	if (ret)
		goto out;
	sector = start_sector << (sdio->blkbits - 9);
	nr_pages = min(sdio->pages_in_io, BIO_MAX_PAGES);
	BUG_ON(nr_pages <= 0);
	dio_bio_alloc(dio, sdio, map_bh->b_bdev, sector, nr_pages);
	sdio->boundary = 0;
out:
	return ret;
}
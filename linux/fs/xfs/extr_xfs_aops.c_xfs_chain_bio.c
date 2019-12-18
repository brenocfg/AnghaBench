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
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_write_hint; int /*<<< orphan*/  bi_opf; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_copy_dev (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static struct bio *
xfs_chain_bio(
	struct bio		*prev)
{
	struct bio *new;

	new = bio_alloc(GFP_NOFS, BIO_MAX_PAGES);
	bio_copy_dev(new, prev);/* also copies over blkcg information */
	new->bi_iter.bi_sector = bio_end_sector(prev);
	new->bi_opf = prev->bi_opf;
	new->bi_write_hint = prev->bi_write_hint;

	bio_chain(prev, new);
	bio_get(prev);		/* for xfs_destroy_ioend */
	submit_bio(prev);
	return new;
}
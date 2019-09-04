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
struct buffer_head {int /*<<< orphan*/  (* b_end_io ) (struct buffer_head*,int) ;int /*<<< orphan*/  b_state; } ;
struct bio {int /*<<< orphan*/  bi_status; struct buffer_head* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Quiet ; 
 int /*<<< orphan*/  BIO_QUIET ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct buffer_head*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_bio_bh_io_sync(struct bio *bio)
{
	struct buffer_head *bh = bio->bi_private;

	if (unlikely(bio_flagged(bio, BIO_QUIET)))
		set_bit(BH_Quiet, &bh->b_state);

	bh->b_end_io(bh, !bio->bi_status);
	bio_put(bio);
}
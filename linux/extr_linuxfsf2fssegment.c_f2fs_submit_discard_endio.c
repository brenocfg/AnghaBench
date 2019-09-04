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
struct discard_cmd {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  bio_ref; int /*<<< orphan*/  error; } ;
struct bio {int /*<<< orphan*/  bi_status; scalar_t__ bi_private; } ;

/* Variables and functions */
 scalar_t__ D_DONE ; 
 scalar_t__ D_SUBMIT ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void f2fs_submit_discard_endio(struct bio *bio)
{
	struct discard_cmd *dc = (struct discard_cmd *)bio->bi_private;
	unsigned long flags;

	dc->error = blk_status_to_errno(bio->bi_status);

	spin_lock_irqsave(&dc->lock, flags);
	dc->bio_ref--;
	if (!dc->bio_ref && dc->state == D_SUBMIT) {
		dc->state = D_DONE;
		complete_all(&dc->wait);
	}
	spin_unlock_irqrestore(&dc->lock, flags);
	bio_put(bio);
}
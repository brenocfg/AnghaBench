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
struct dio {int refcount; int /*<<< orphan*/  bio_lock; scalar_t__ waiter; struct dio* bio_list; struct dio* bi_private; } ;
struct bio {int refcount; int /*<<< orphan*/  bio_lock; scalar_t__ waiter; struct bio* bio_list; struct bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void dio_bio_end_io(struct bio *bio)
{
	struct dio *dio = bio->bi_private;
	unsigned long flags;

	spin_lock_irqsave(&dio->bio_lock, flags);
	bio->bi_private = dio->bio_list;
	dio->bio_list = bio;
	if (--dio->refcount == 1 && dio->waiter)
		wake_up_process(dio->waiter);
	spin_unlock_irqrestore(&dio->bio_lock, flags);
}
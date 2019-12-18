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
struct TYPE_3__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  last_queue; } ;
struct iomap_dio {TYPE_1__ submit; TYPE_2__* iocb; int /*<<< orphan*/  ref; } ;
struct iomap {int /*<<< orphan*/  bdev; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {int ki_flags; } ;

/* Variables and functions */
 int IOCB_HIPRI ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_polled (struct bio*,TYPE_2__*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void iomap_dio_submit_bio(struct iomap_dio *dio, struct iomap *iomap,
		struct bio *bio)
{
	atomic_inc(&dio->ref);

	if (dio->iocb->ki_flags & IOCB_HIPRI)
		bio_set_polled(bio, dio->iocb);

	dio->submit.last_queue = bdev_get_queue(iomap->bdev);
	dio->submit.cookie = submit_bio(bio);
}
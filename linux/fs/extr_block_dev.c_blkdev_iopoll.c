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
struct request_queue {int dummy; } ;
struct kiocb {int /*<<< orphan*/  ki_cookie; TYPE_2__* ki_filp; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct block_device* I_BDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int blk_poll (struct request_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int blkdev_iopoll(struct kiocb *kiocb, bool wait)
{
	struct block_device *bdev = I_BDEV(kiocb->ki_filp->f_mapping->host);
	struct request_queue *q = bdev_get_queue(bdev);

	return blk_poll(q, READ_ONCE(kiocb->ki_cookie), wait);
}
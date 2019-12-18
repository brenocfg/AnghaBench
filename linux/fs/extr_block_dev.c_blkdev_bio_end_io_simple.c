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
struct task_struct {int dummy; } ;
struct bio {struct task_struct* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_wake_io_task (struct task_struct*) ; 

__attribute__((used)) static void blkdev_bio_end_io_simple(struct bio *bio)
{
	struct task_struct *waiter = bio->bi_private;

	WRITE_ONCE(bio->bi_private, NULL);
	blk_wake_io_task(waiter);
}
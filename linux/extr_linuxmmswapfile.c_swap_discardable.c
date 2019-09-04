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
struct swap_info_struct {int /*<<< orphan*/  bdev; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 

__attribute__((used)) static bool swap_discardable(struct swap_info_struct *si)
{
	struct request_queue *q = bdev_get_queue(si->bdev);

	if (!q || !blk_queue_discard(q))
		return false;

	return true;
}
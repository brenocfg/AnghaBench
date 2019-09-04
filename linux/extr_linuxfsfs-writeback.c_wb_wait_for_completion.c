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
struct wb_completion {int /*<<< orphan*/  cnt; } ;
struct backing_dev_info {int /*<<< orphan*/  wb_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wb_wait_for_completion(struct backing_dev_info *bdi,
				   struct wb_completion *done)
{
	atomic_dec(&done->cnt);		/* put down the initial count */
	wait_event(bdi->wb_waitq, !atomic_read(&done->cnt));
}
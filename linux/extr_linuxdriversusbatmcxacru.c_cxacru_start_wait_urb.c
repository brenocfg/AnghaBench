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
struct urb {int actual_length; int status; } ;
struct cxacru_timer {int /*<<< orphan*/  timer; struct urb* urb; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMEOUT ; 
 int /*<<< orphan*/  cxacru_timeout_kill ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_timer_on_stack (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup_on_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static int cxacru_start_wait_urb(struct urb *urb, struct completion *done,
				 int *actual_length)
{
	struct cxacru_timer timer = {
		.urb = urb,
	};

	timer_setup_on_stack(&timer.timer, cxacru_timeout_kill, 0);
	mod_timer(&timer.timer, jiffies + msecs_to_jiffies(CMD_TIMEOUT));
	wait_for_completion(done);
	del_timer_sync(&timer.timer);
	destroy_timer_on_stack(&timer.timer);

	if (actual_length)
		*actual_length = urb->actual_length;
	return urb->status; /* must read status after completion */
}
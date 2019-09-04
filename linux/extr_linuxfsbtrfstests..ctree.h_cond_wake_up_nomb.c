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
struct wait_queue_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ waitqueue_active (struct wait_queue_head*) ; 
 int /*<<< orphan*/  wake_up (struct wait_queue_head*) ; 

__attribute__((used)) static inline void cond_wake_up_nomb(struct wait_queue_head *wq)
{
	/*
	 * Special case for conditional wakeup where the barrier required for
	 * waitqueue_active is implied by some of the preceding code. Eg. one
	 * of such atomic operations (atomic_dec_and_return, ...), or a
	 * unlock/lock sequence, etc.
	 */
	if (waitqueue_active(wq))
		wake_up(wq);
}
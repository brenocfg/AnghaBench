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
 int /*<<< orphan*/  wake_up (struct wait_queue_head*) ; 
 scalar_t__ wq_has_sleeper (struct wait_queue_head*) ; 

__attribute__((used)) static inline void cond_wake_up(struct wait_queue_head *wq)
{
	/*
	 * This implies a full smp_mb barrier, see comments for
	 * waitqueue_active why.
	 */
	if (wq_has_sleeper(wq))
		wake_up(wq);
}
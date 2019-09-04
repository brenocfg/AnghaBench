#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;
struct request_queue {int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  queue_lock; TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void queue_flag_set_unlocked(unsigned int flag,
					   struct request_queue *q)
{
	if (test_bit(QUEUE_FLAG_INIT_DONE, &q->queue_flags) &&
	    kref_read(&q->kobj.kref))
		lockdep_assert_held(q->queue_lock);
	__set_bit(flag, &q->queue_flags);
}
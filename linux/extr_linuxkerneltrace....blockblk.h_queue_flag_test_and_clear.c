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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_lockdep_assert_held (struct request_queue*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int queue_flag_test_and_clear(unsigned int flag,
					    struct request_queue *q)
{
	queue_lockdep_assert_held(q);

	if (test_bit(flag, &q->queue_flags)) {
		__clear_bit(flag, &q->queue_flags);
		return 1;
	}

	return 0;
}
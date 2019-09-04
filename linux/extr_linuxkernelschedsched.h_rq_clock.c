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
typedef  int /*<<< orphan*/  u64 ;
struct rq {int /*<<< orphan*/  clock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_clock_updated (struct rq*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u64 rq_clock(struct rq *rq)
{
	lockdep_assert_held(&rq->lock);
	assert_clock_updated(rq);

	return rq->clock;
}
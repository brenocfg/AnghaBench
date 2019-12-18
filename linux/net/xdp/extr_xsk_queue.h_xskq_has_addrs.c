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
typedef  scalar_t__ u32 ;
struct xsk_queue {scalar_t__ prod_tail; scalar_t__ cons_tail; TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  producer; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xskq_has_addrs(struct xsk_queue *q, u32 cnt)
{
	u32 entries = q->prod_tail - q->cons_tail;

	if (entries >= cnt)
		return true;

	/* Refresh the local pointer. */
	q->prod_tail = READ_ONCE(q->ring->producer);
	entries = q->prod_tail - q->cons_tail;

	return entries >= cnt;
}
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
struct xsk_queue {int /*<<< orphan*/  prod_tail; TYPE_1__* ring; int /*<<< orphan*/  prod_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  producer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline void xskq_produce_flush_desc(struct xsk_queue *q)
{
	/* Order producer and data */
	smp_wmb(); /* B, matches C */

	q->prod_tail = q->prod_head;
	WRITE_ONCE(q->ring->producer, q->prod_tail);
}
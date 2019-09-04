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
struct xsk_queue {scalar_t__ nentries; scalar_t__ cons_tail; TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 xskq_nb_free(struct xsk_queue *q, u32 producer, u32 dcnt)
{
	u32 free_entries = q->nentries - (producer - q->cons_tail);

	if (free_entries >= dcnt)
		return free_entries;

	/* Refresh the local tail pointer */
	q->cons_tail = READ_ONCE(q->ring->consumer);
	return q->nentries - (producer - q->cons_tail);
}
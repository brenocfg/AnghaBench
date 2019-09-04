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
struct xenvif_queue {unsigned long credit_bytes; unsigned long remaining_credit; int rate_limited; } ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static void tx_add_credit(struct xenvif_queue *queue)
{
	unsigned long max_burst, max_credit;

	/*
	 * Allow a burst big enough to transmit a jumbo packet of up to 128kB.
	 * Otherwise the interface can seize up due to insufficient credit.
	 */
	max_burst = max(131072UL, queue->credit_bytes);

	/* Take care that adding a new chunk of credit doesn't wrap to zero. */
	max_credit = queue->remaining_credit + queue->credit_bytes;
	if (max_credit < queue->remaining_credit)
		max_credit = ULONG_MAX; /* wrapped: clamp to ULONG_MAX */

	queue->remaining_credit = min(max_credit, max_burst);
	queue->rate_limited = false;
}
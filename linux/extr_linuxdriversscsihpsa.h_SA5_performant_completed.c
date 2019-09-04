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
typedef  size_t u8 ;
typedef  int u32 ;
struct reply_queue_buffer {unsigned long* head; size_t current_entry; int wraparound; } ;
struct ctlr_info {size_t max_commands; int /*<<< orphan*/  commands_outstanding; scalar_t__ vaddr; scalar_t__ msix_vectors; TYPE_1__* pdev; struct reply_queue_buffer* reply_queue; } ;
struct TYPE_2__ {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 unsigned long FIFO_EMPTY ; 
 scalar_t__ SA5_OUTDB_CLEAR ; 
 int /*<<< orphan*/  SA5_OUTDB_CLEAR_PERF_BIT ; 
 scalar_t__ SA5_OUTDB_STATUS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long SA5_performant_completed(struct ctlr_info *h, u8 q)
{
	struct reply_queue_buffer *rq = &h->reply_queue[q];
	unsigned long register_value = FIFO_EMPTY;

	/* msi auto clears the interrupt pending bit. */
	if (unlikely(!(h->pdev->msi_enabled || h->msix_vectors))) {
		/* flush the controller write of the reply queue by reading
		 * outbound doorbell status register.
		 */
		(void) readl(h->vaddr + SA5_OUTDB_STATUS);
		writel(SA5_OUTDB_CLEAR_PERF_BIT, h->vaddr + SA5_OUTDB_CLEAR);
		/* Do a read in order to flush the write to the controller
		 * (as per spec.)
		 */
		(void) readl(h->vaddr + SA5_OUTDB_STATUS);
	}

	if ((((u32) rq->head[rq->current_entry]) & 1) == rq->wraparound) {
		register_value = rq->head[rq->current_entry];
		rq->current_entry++;
		atomic_dec(&h->commands_outstanding);
	} else {
		register_value = FIFO_EMPTY;
	}
	/* Check for wraparound */
	if (rq->current_entry == h->max_commands) {
		rq->current_entry = 0;
		rq->wraparound ^= 1;
	}
	return register_value;
}
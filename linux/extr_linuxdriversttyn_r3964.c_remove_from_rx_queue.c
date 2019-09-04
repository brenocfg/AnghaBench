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
struct r3964_info {int /*<<< orphan*/  blocks_in_rx_queue; struct r3964_block_header* rx_last; struct r3964_block_header* rx_first; int /*<<< orphan*/  lock; } ;
struct r3964_block_header {struct r3964_block_header* next; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_M (char*,struct r3964_block_header*) ; 
 int /*<<< orphan*/  TRACE_Q (char*,struct r3964_block_header*,struct r3964_block_header*,...) ; 
 int /*<<< orphan*/  kfree (struct r3964_block_header*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void remove_from_rx_queue(struct r3964_info *pInfo,
				 struct r3964_block_header *pHeader)
{
	unsigned long flags;
	struct r3964_block_header *pFind;

	if (pHeader == NULL)
		return;

	TRACE_Q("remove_from_rx_queue: rx_first = %p, rx_last = %p, count = %d",
		pInfo->rx_first, pInfo->rx_last, pInfo->blocks_in_rx_queue);
	TRACE_Q("remove_from_rx_queue: %p, length %u",
		pHeader, pHeader->length);

	spin_lock_irqsave(&pInfo->lock, flags);

	if (pInfo->rx_first == pHeader) {
		/* Remove the first block in the linked list: */
		pInfo->rx_first = pHeader->next;

		if (pInfo->rx_first == NULL) {
			pInfo->rx_last = NULL;
		}
		pInfo->blocks_in_rx_queue--;
	} else {
		/* Find block to remove: */
		for (pFind = pInfo->rx_first; pFind; pFind = pFind->next) {
			if (pFind->next == pHeader) {
				/* Got it. */
				pFind->next = pHeader->next;
				pInfo->blocks_in_rx_queue--;
				if (pFind->next == NULL) {
					/* Oh, removed the last one! */
					pInfo->rx_last = pFind;
				}
				break;
			}
		}
	}

	spin_unlock_irqrestore(&pInfo->lock, flags);

	kfree(pHeader);
	TRACE_M("remove_from_rx_queue - kfree %p", pHeader);

	TRACE_Q("remove_from_rx_queue: rx_first = %p, rx_last = %p, count = %d",
		pInfo->rx_first, pInfo->rx_last, pInfo->blocks_in_rx_queue);
}
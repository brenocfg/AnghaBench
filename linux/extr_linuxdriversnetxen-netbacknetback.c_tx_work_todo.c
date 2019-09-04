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
struct xenvif_queue {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_HAS_UNCONSUMED_REQUESTS (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tx_work_todo(struct xenvif_queue *queue)
{
	if (likely(RING_HAS_UNCONSUMED_REQUESTS(&queue->tx)))
		return 1;

	return 0;
}
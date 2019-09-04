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
struct xenvif_queue {int /*<<< orphan*/  pages_to_map; int /*<<< orphan*/  tx_map_ops; int /*<<< orphan*/  tx_copy_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  gnttab_batch_copy (int /*<<< orphan*/ ,unsigned int) ; 
 int gnttab_map_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tx_work_todo (struct xenvif_queue*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xenvif_tx_build_gops (struct xenvif_queue*,int,unsigned int*,unsigned int*) ; 
 int xenvif_tx_submit (struct xenvif_queue*) ; 

int xenvif_tx_action(struct xenvif_queue *queue, int budget)
{
	unsigned nr_mops, nr_cops = 0;
	int work_done, ret;

	if (unlikely(!tx_work_todo(queue)))
		return 0;

	xenvif_tx_build_gops(queue, budget, &nr_cops, &nr_mops);

	if (nr_cops == 0)
		return 0;

	gnttab_batch_copy(queue->tx_copy_ops, nr_cops);
	if (nr_mops != 0) {
		ret = gnttab_map_refs(queue->tx_map_ops,
				      NULL,
				      queue->pages_to_map,
				      nr_mops);
		BUG_ON(ret);
	}

	work_done = xenvif_tx_submit(queue);

	return work_done;
}
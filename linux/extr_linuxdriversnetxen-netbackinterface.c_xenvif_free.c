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
struct xenvif_queue {int dummy; } ;
struct xenvif {unsigned int num_queues; int /*<<< orphan*/  dev; struct xenvif_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_deinit_queue (struct xenvif_queue*) ; 

void xenvif_free(struct xenvif *vif)
{
	struct xenvif_queue *queues = vif->queues;
	unsigned int num_queues = vif->num_queues;
	unsigned int queue_index;

	unregister_netdev(vif->dev);
	free_netdev(vif->dev);

	for (queue_index = 0; queue_index < num_queues; ++queue_index)
		xenvif_deinit_queue(&queues[queue_index]);
	vfree(queues);

	module_put(THIS_MODULE);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdp_frame {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct xdp_bulk_queue {scalar_t__ count; TYPE_2__ flush_node; struct xdp_frame** q; struct net_device* dev_rx; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;
struct bpf_dtab_netdev {int /*<<< orphan*/  bulkq; TYPE_1__* dtab; } ;
struct TYPE_3__ {int /*<<< orphan*/  flush_list; } ;

/* Variables and functions */
 scalar_t__ DEV_MAP_BULK_SIZE ; 
 int /*<<< orphan*/  bq_xmit_all (struct xdp_bulk_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add (TYPE_2__*,struct list_head*) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bq_enqueue(struct bpf_dtab_netdev *obj, struct xdp_frame *xdpf,
		      struct net_device *dev_rx)

{
	struct list_head *flush_list = this_cpu_ptr(obj->dtab->flush_list);
	struct xdp_bulk_queue *bq = this_cpu_ptr(obj->bulkq);

	if (unlikely(bq->count == DEV_MAP_BULK_SIZE))
		bq_xmit_all(bq, 0, true);

	/* Ingress dev_rx will be the same for all xdp_frame's in
	 * bulk_queue, because bq stored per-CPU and must be flushed
	 * from net_device drivers NAPI func end.
	 */
	if (!bq->dev_rx)
		bq->dev_rx = dev_rx;

	bq->q[bq->count++] = xdpf;

	if (!bq->flush_node.prev)
		list_add(&bq->flush_node, flush_list);

	return 0;
}
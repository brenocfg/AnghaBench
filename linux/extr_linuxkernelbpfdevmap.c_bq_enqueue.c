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
struct xdp_frame {int dummy; } ;
struct xdp_bulk_queue {scalar_t__ count; struct xdp_frame** q; struct net_device* dev_rx; } ;
struct net_device {int dummy; } ;
struct bpf_dtab_netdev {int /*<<< orphan*/  bulkq; } ;

/* Variables and functions */
 scalar_t__ DEV_MAP_BULK_SIZE ; 
 int /*<<< orphan*/  bq_xmit_all (struct bpf_dtab_netdev*,struct xdp_bulk_queue*,int /*<<< orphan*/ ,int) ; 
 struct xdp_bulk_queue* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bq_enqueue(struct bpf_dtab_netdev *obj, struct xdp_frame *xdpf,
		      struct net_device *dev_rx)

{
	struct xdp_bulk_queue *bq = this_cpu_ptr(obj->bulkq);

	if (unlikely(bq->count == DEV_MAP_BULK_SIZE))
		bq_xmit_all(obj, bq, 0, true);

	/* Ingress dev_rx will be the same for all xdp_frame's in
	 * bulk_queue, because bq stored per-CPU and must be flushed
	 * from net_device drivers NAPI func end.
	 */
	if (!bq->dev_rx)
		bq->dev_rx = dev_rx;

	bq->q[bq->count++] = xdpf;
	return 0;
}
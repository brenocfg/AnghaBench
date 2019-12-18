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
struct xdp_bulk_queue {int count; int /*<<< orphan*/  flush_node; struct xdp_frame** q; struct bpf_cpu_map_entry* obj; } ;
struct ptr_ring {int /*<<< orphan*/  producer_lock; } ;
struct bpf_cpu_map_entry {int cpu; int /*<<< orphan*/  map_id; struct ptr_ring* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_del_clearprev (int /*<<< orphan*/ *) ; 
 int __ptr_ring_produce (struct ptr_ring*,struct xdp_frame*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xdp_cpumap_enqueue (int /*<<< orphan*/ ,unsigned int,unsigned int,int const) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int bq_flush_to_queue(struct xdp_bulk_queue *bq, bool in_napi_ctx)
{
	struct bpf_cpu_map_entry *rcpu = bq->obj;
	unsigned int processed = 0, drops = 0;
	const int to_cpu = rcpu->cpu;
	struct ptr_ring *q;
	int i;

	if (unlikely(!bq->count))
		return 0;

	q = rcpu->queue;
	spin_lock(&q->producer_lock);

	for (i = 0; i < bq->count; i++) {
		struct xdp_frame *xdpf = bq->q[i];
		int err;

		err = __ptr_ring_produce(q, xdpf);
		if (err) {
			drops++;
			if (likely(in_napi_ctx))
				xdp_return_frame_rx_napi(xdpf);
			else
				xdp_return_frame(xdpf);
		}
		processed++;
	}
	bq->count = 0;
	spin_unlock(&q->producer_lock);

	__list_del_clearprev(&bq->flush_node);

	/* Feedback loop via tracepoints */
	trace_xdp_cpumap_enqueue(rcpu->map_id, processed, drops, to_cpu);
	return 0;
}
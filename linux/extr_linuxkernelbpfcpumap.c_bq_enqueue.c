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
struct xdp_bulk_queue {scalar_t__ count; struct xdp_frame** q; } ;
struct bpf_cpu_map_entry {int /*<<< orphan*/  bulkq; } ;

/* Variables and functions */
 scalar_t__ CPU_MAP_BULK_SIZE ; 
 int /*<<< orphan*/  bq_flush_to_queue (struct bpf_cpu_map_entry*,struct xdp_bulk_queue*,int) ; 
 struct xdp_bulk_queue* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bq_enqueue(struct bpf_cpu_map_entry *rcpu, struct xdp_frame *xdpf)
{
	struct xdp_bulk_queue *bq = this_cpu_ptr(rcpu->bulkq);

	if (unlikely(bq->count == CPU_MAP_BULK_SIZE))
		bq_flush_to_queue(rcpu, bq, true);

	/* Notice, xdp_buff/page MUST be queued here, long enough for
	 * driver to code invoking us to finished, due to driver
	 * (e.g. ixgbe) recycle tricks based on page-refcnt.
	 *
	 * Thus, incoming xdp_frame is always queued here (else we race
	 * with another CPU on page-refcnt and remaining driver code).
	 * Queue time is very short, as driver will invoke flush
	 * operation, when completing napi->poll call.
	 */
	bq->q[bq->count++] = xdpf;
	return 0;
}
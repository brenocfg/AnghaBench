#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct fq_codel_sched_data {unsigned int flows_cnt; unsigned int* backlogs; unsigned int memory_usage; struct fq_codel_flow* flows; } ;
struct TYPE_5__ {unsigned int count; } ;
struct fq_codel_flow {TYPE_1__ cvars; } ;
struct TYPE_7__ {unsigned int qlen; } ;
struct TYPE_6__ {unsigned int drops; unsigned int backlog; } ;
struct Qdisc {TYPE_3__ q; TYPE_2__ qstats; } ;
struct TYPE_8__ {scalar_t__ mem_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qdisc_drop (struct sk_buff*,struct sk_buff**) ; 
 struct sk_buff* dequeue_head (struct fq_codel_flow*) ; 
 TYPE_4__* get_codel_cb (struct sk_buff*) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct fq_codel_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static unsigned int fq_codel_drop(struct Qdisc *sch, unsigned int max_packets,
				  struct sk_buff **to_free)
{
	struct fq_codel_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;
	unsigned int maxbacklog = 0, idx = 0, i, len;
	struct fq_codel_flow *flow;
	unsigned int threshold;
	unsigned int mem = 0;

	/* Queue is full! Find the fat flow and drop packet(s) from it.
	 * This might sound expensive, but with 1024 flows, we scan
	 * 4KB of memory, and we dont need to handle a complex tree
	 * in fast path (packet queue/enqueue) with many cache misses.
	 * In stress mode, we'll try to drop 64 packets from the flow,
	 * amortizing this linear lookup to one cache line per drop.
	 */
	for (i = 0; i < q->flows_cnt; i++) {
		if (q->backlogs[i] > maxbacklog) {
			maxbacklog = q->backlogs[i];
			idx = i;
		}
	}

	/* Our goal is to drop half of this fat flow backlog */
	threshold = maxbacklog >> 1;

	flow = &q->flows[idx];
	len = 0;
	i = 0;
	do {
		skb = dequeue_head(flow);
		len += qdisc_pkt_len(skb);
		mem += get_codel_cb(skb)->mem_usage;
		__qdisc_drop(skb, to_free);
	} while (++i < max_packets && len < threshold);

	/* Tell codel to increase its signal strength also */
	flow->cvars.count += i;
	q->backlogs[idx] -= len;
	q->memory_usage -= mem;
	sch->qstats.drops += i;
	sch->qstats.backlog -= len;
	sch->q.qlen -= i;
	return idx;
}
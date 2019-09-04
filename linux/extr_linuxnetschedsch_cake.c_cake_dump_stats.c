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
struct nlattr {int dummy; } ;
struct gnet_dump {int /*<<< orphan*/  skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  target; } ;
struct cake_tin_data {int tin_backlog; int packets; int tin_dropped; int tin_ecn_mark; int ack_drops; int way_hits; int way_misses; int way_collisions; int sparse_flow_count; int decaying_flow_count; int bulk_flow_count; int unresponsive_flow_count; int max_skblen; int flow_quantum; int /*<<< orphan*/  base_delay; int /*<<< orphan*/  avge_delay; int /*<<< orphan*/  peak_delay; TYPE_1__ cparams; int /*<<< orphan*/  bytes; int /*<<< orphan*/  tin_rate_bps; } ;
struct cake_sched_data {int buffer_limit; int buffer_max_used; int avg_netoff; int max_netlen; int max_adjlen; int min_netlen; int min_adjlen; int tin_cnt; size_t* tin_order; struct cake_tin_data* tins; int /*<<< orphan*/  avg_peak_bandwidth; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_CAKE_STATS_AVG_NETOFF ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_CAPACITY_ESTIMATE64 ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MAX_ADJLEN ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MAX_NETLEN ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MEMORY_LIMIT ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MEMORY_USED ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MIN_ADJLEN ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_MIN_NETLEN ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_PAD ; 
 int TCA_CAKE_STATS_TIN_STATS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_ACKS_DROPPED_PACKETS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_AVG_DELAY_US ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_BACKLOG_BYTES ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_BASE_DELAY_US ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_BULK_FLOWS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_DROPPED_PACKETS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_ECN_MARKED_PACKETS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_FLOW_QUANTUM ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_INTERVAL_US ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_MAX_SKBLEN ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_PAD ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_PEAK_DELAY_US ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_SENT_BYTES64 ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_SENT_PACKETS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_SPARSE_FLOWS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_TARGET_US ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_THRESHOLD_RATE64 ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_UNRESPONSIVE_FLOWS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_WAY_COLLISIONS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_WAY_INDIRECT_HITS ; 
 int /*<<< orphan*/  TCA_CAKE_TIN_STATS_WAY_MISSES ; 
 int TCA_STATS_APP ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u64_64bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int cake_dump_stats(struct Qdisc *sch, struct gnet_dump *d)
{
	struct nlattr *stats = nla_nest_start(d->skb, TCA_STATS_APP);
	struct cake_sched_data *q = qdisc_priv(sch);
	struct nlattr *tstats, *ts;
	int i;

	if (!stats)
		return -1;

#define PUT_STAT_U32(attr, data) do {				       \
		if (nla_put_u32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			goto nla_put_failure;			       \
	} while (0)
#define PUT_STAT_U64(attr, data) do {				       \
		if (nla_put_u64_64bit(d->skb, TCA_CAKE_STATS_ ## attr, \
					data, TCA_CAKE_STATS_PAD)) \
			goto nla_put_failure;			       \
	} while (0)

	PUT_STAT_U64(CAPACITY_ESTIMATE64, q->avg_peak_bandwidth);
	PUT_STAT_U32(MEMORY_LIMIT, q->buffer_limit);
	PUT_STAT_U32(MEMORY_USED, q->buffer_max_used);
	PUT_STAT_U32(AVG_NETOFF, ((q->avg_netoff + 0x8000) >> 16));
	PUT_STAT_U32(MAX_NETLEN, q->max_netlen);
	PUT_STAT_U32(MAX_ADJLEN, q->max_adjlen);
	PUT_STAT_U32(MIN_NETLEN, q->min_netlen);
	PUT_STAT_U32(MIN_ADJLEN, q->min_adjlen);

#undef PUT_STAT_U32
#undef PUT_STAT_U64

	tstats = nla_nest_start(d->skb, TCA_CAKE_STATS_TIN_STATS);
	if (!tstats)
		goto nla_put_failure;

#define PUT_TSTAT_U32(attr, data) do {					\
		if (nla_put_u32(d->skb, TCA_CAKE_TIN_STATS_ ## attr, data)) \
			goto nla_put_failure;				\
	} while (0)
#define PUT_TSTAT_U64(attr, data) do {					\
		if (nla_put_u64_64bit(d->skb, TCA_CAKE_TIN_STATS_ ## attr, \
					data, TCA_CAKE_TIN_STATS_PAD))	\
			goto nla_put_failure;				\
	} while (0)

	for (i = 0; i < q->tin_cnt; i++) {
		struct cake_tin_data *b = &q->tins[q->tin_order[i]];

		ts = nla_nest_start(d->skb, i + 1);
		if (!ts)
			goto nla_put_failure;

		PUT_TSTAT_U64(THRESHOLD_RATE64, b->tin_rate_bps);
		PUT_TSTAT_U64(SENT_BYTES64, b->bytes);
		PUT_TSTAT_U32(BACKLOG_BYTES, b->tin_backlog);

		PUT_TSTAT_U32(TARGET_US,
			      ktime_to_us(ns_to_ktime(b->cparams.target)));
		PUT_TSTAT_U32(INTERVAL_US,
			      ktime_to_us(ns_to_ktime(b->cparams.interval)));

		PUT_TSTAT_U32(SENT_PACKETS, b->packets);
		PUT_TSTAT_U32(DROPPED_PACKETS, b->tin_dropped);
		PUT_TSTAT_U32(ECN_MARKED_PACKETS, b->tin_ecn_mark);
		PUT_TSTAT_U32(ACKS_DROPPED_PACKETS, b->ack_drops);

		PUT_TSTAT_U32(PEAK_DELAY_US,
			      ktime_to_us(ns_to_ktime(b->peak_delay)));
		PUT_TSTAT_U32(AVG_DELAY_US,
			      ktime_to_us(ns_to_ktime(b->avge_delay)));
		PUT_TSTAT_U32(BASE_DELAY_US,
			      ktime_to_us(ns_to_ktime(b->base_delay)));

		PUT_TSTAT_U32(WAY_INDIRECT_HITS, b->way_hits);
		PUT_TSTAT_U32(WAY_MISSES, b->way_misses);
		PUT_TSTAT_U32(WAY_COLLISIONS, b->way_collisions);

		PUT_TSTAT_U32(SPARSE_FLOWS, b->sparse_flow_count +
					    b->decaying_flow_count);
		PUT_TSTAT_U32(BULK_FLOWS, b->bulk_flow_count);
		PUT_TSTAT_U32(UNRESPONSIVE_FLOWS, b->unresponsive_flow_count);
		PUT_TSTAT_U32(MAX_SKBLEN, b->max_skblen);

		PUT_TSTAT_U32(FLOW_QUANTUM, b->flow_quantum);
		nla_nest_end(d->skb, ts);
	}

#undef PUT_TSTAT_U32
#undef PUT_TSTAT_U64

	nla_nest_end(d->skb, tstats);
	return nla_nest_end(d->skb, stats);

nla_put_failure:
	nla_nest_cancel(d->skb, stats);
	return -1;
}
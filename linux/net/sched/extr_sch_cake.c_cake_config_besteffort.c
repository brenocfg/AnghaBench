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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct cake_tin_data {int tin_quantum_band; int tin_quantum_prio; } ;
struct cake_sched_data {int tin_cnt; int /*<<< orphan*/  interval; int /*<<< orphan*/  target; int /*<<< orphan*/  tin_order; int /*<<< orphan*/  tin_index; int /*<<< orphan*/  rate_bps; struct cake_tin_data* tins; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  besteffort ; 
 int /*<<< orphan*/  cake_set_rate (struct cake_tin_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normal_order ; 
 int /*<<< orphan*/  psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  us_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cake_config_besteffort(struct Qdisc *sch)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	struct cake_tin_data *b = &q->tins[0];
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 rate = q->rate_bps;

	q->tin_cnt = 1;

	q->tin_index = besteffort;
	q->tin_order = normal_order;

	cake_set_rate(b, rate, mtu,
		      us_to_ns(q->target), us_to_ns(q->interval));
	b->tin_quantum_band = 65535;
	b->tin_quantum_prio = 65535;

	return 0;
}
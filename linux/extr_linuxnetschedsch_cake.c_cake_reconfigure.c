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
typedef  int u64 ;
struct cake_sched_data {int tin_mode; int tin_cnt; int rate_bps; int interval; scalar_t__ buffer_config_limit; scalar_t__ buffer_limit; TYPE_2__* tins; int /*<<< orphan*/  rate_shft; int /*<<< orphan*/  rate_ns; } ;
struct Qdisc {int limit; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  tin_rate_shft; int /*<<< orphan*/  tin_rate_ns; TYPE_1__ cparams; } ;

/* Variables and functions */
#define  CAKE_DIFFSERV_BESTEFFORT 132 
#define  CAKE_DIFFSERV_DIFFSERV3 131 
#define  CAKE_DIFFSERV_DIFFSERV4 130 
#define  CAKE_DIFFSERV_DIFFSERV8 129 
#define  CAKE_DIFFSERV_PRECEDENCE 128 
 int CAKE_MAX_TINS ; 
 int /*<<< orphan*/  TCQ_F_CAN_BYPASS ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  cake_clear_tin (struct Qdisc*,int) ; 
 int cake_config_besteffort (struct Qdisc*) ; 
 int cake_config_diffserv3 (struct Qdisc*) ; 
 int cake_config_diffserv4 (struct Qdisc*) ; 
 int cake_config_diffserv8 (struct Qdisc*) ; 
 int cake_config_precedence (struct Qdisc*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  max (int,scalar_t__) ; 
 scalar_t__ max_t (int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void cake_reconfigure(struct Qdisc *sch)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	int c, ft;

	switch (q->tin_mode) {
	case CAKE_DIFFSERV_BESTEFFORT:
		ft = cake_config_besteffort(sch);
		break;

	case CAKE_DIFFSERV_PRECEDENCE:
		ft = cake_config_precedence(sch);
		break;

	case CAKE_DIFFSERV_DIFFSERV8:
		ft = cake_config_diffserv8(sch);
		break;

	case CAKE_DIFFSERV_DIFFSERV4:
		ft = cake_config_diffserv4(sch);
		break;

	case CAKE_DIFFSERV_DIFFSERV3:
	default:
		ft = cake_config_diffserv3(sch);
		break;
	}

	for (c = q->tin_cnt; c < CAKE_MAX_TINS; c++) {
		cake_clear_tin(sch, c);
		q->tins[c].cparams.mtu_time = q->tins[ft].cparams.mtu_time;
	}

	q->rate_ns   = q->tins[ft].tin_rate_ns;
	q->rate_shft = q->tins[ft].tin_rate_shft;

	if (q->buffer_config_limit) {
		q->buffer_limit = q->buffer_config_limit;
	} else if (q->rate_bps) {
		u64 t = q->rate_bps * q->interval;

		do_div(t, USEC_PER_SEC / 4);
		q->buffer_limit = max_t(u32, t, 4U << 20);
	} else {
		q->buffer_limit = ~0;
	}

	sch->flags &= ~TCQ_F_CAN_BYPASS;

	q->buffer_limit = min(q->buffer_limit,
			      max(sch->limit * psched_mtu(qdisc_dev(sch)),
				  q->buffer_config_limit));
}
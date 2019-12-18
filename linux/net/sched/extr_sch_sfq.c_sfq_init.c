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
struct sfq_sched_data {int limit; int maxdepth; int divisor; int maxflows; int /*<<< orphan*/ * slots; int /*<<< orphan*/ * ht; int /*<<< orphan*/  perturbation; scalar_t__ perturb_period; int /*<<< orphan*/  quantum; int /*<<< orphan*/  scaled_quantum; int /*<<< orphan*/ * tail; scalar_t__ cur_depth; TYPE_1__* dep; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  block; int /*<<< orphan*/  perturb_timer; struct Qdisc* sch; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {void* prev; void* next; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SFQ_ALLOT_SIZE (int /*<<< orphan*/ ) ; 
 int SFQ_DEFAULT_FLOWS ; 
 int SFQ_DEFAULT_HASH_DIVISOR ; 
 int /*<<< orphan*/  SFQ_EMPTY_SLOT ; 
 int SFQ_MAX_DEPTH ; 
 void* SFQ_MAX_FLOWS ; 
 int /*<<< orphan*/  TCQ_F_CAN_BYPASS ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 void* sfq_alloc (int) ; 
 int sfq_change (struct Qdisc*,struct nlattr*) ; 
 int /*<<< orphan*/  sfq_link (struct sfq_sched_data*,int) ; 
 int /*<<< orphan*/  sfq_perturbation ; 
 int /*<<< orphan*/  slot_queue_init (int /*<<< orphan*/ *) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sfq_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	int i;
	int err;

	q->sch = sch;
	timer_setup(&q->perturb_timer, sfq_perturbation, TIMER_DEFERRABLE);

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	if (err)
		return err;

	for (i = 0; i < SFQ_MAX_DEPTH + 1; i++) {
		q->dep[i].next = i + SFQ_MAX_FLOWS;
		q->dep[i].prev = i + SFQ_MAX_FLOWS;
	}

	q->limit = SFQ_MAX_DEPTH;
	q->maxdepth = SFQ_MAX_DEPTH;
	q->cur_depth = 0;
	q->tail = NULL;
	q->divisor = SFQ_DEFAULT_HASH_DIVISOR;
	q->maxflows = SFQ_DEFAULT_FLOWS;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->scaled_quantum = SFQ_ALLOT_SIZE(q->quantum);
	q->perturb_period = 0;
	get_random_bytes(&q->perturbation, sizeof(q->perturbation));

	if (opt) {
		int err = sfq_change(sch, opt);
		if (err)
			return err;
	}

	q->ht = sfq_alloc(sizeof(q->ht[0]) * q->divisor);
	q->slots = sfq_alloc(sizeof(q->slots[0]) * q->maxflows);
	if (!q->ht || !q->slots) {
		/* Note: sfq_destroy() will be called by our caller */
		return -ENOMEM;
	}

	for (i = 0; i < q->divisor; i++)
		q->ht[i] = SFQ_EMPTY_SLOT;

	for (i = 0; i < q->maxflows; i++) {
		slot_queue_init(&q->slots[i]);
		sfq_link(q, i);
	}
	if (q->limit >= 1)
		sch->flags |= TCQ_F_CAN_BYPASS;
	else
		sch->flags &= ~TCQ_F_CAN_BYPASS;
	return 0;
}
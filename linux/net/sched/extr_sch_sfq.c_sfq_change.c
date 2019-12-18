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
struct tc_sfq_qopt_v1 {int depth; int /*<<< orphan*/  headdrop; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_P; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  Wlog; int /*<<< orphan*/  qth_max; scalar_t__ qth_min; } ;
struct tc_sfq_qopt {int divisor; int perturb_period; int flows; int limit; scalar_t__ quantum; } ;
struct sk_buff {int dummy; } ;
struct sfq_sched_data {int perturb_period; int maxflows; int divisor; int maxdepth; int limit; int /*<<< orphan*/  perturbation; int /*<<< orphan*/  perturb_timer; int /*<<< orphan*/  headdrop; int /*<<< orphan*/  flags; int /*<<< orphan*/  red_parms; scalar_t__ quantum; int /*<<< orphan*/  scaled_quantum; } ;
struct red_parms {int dummy; } ;
struct nlattr {scalar_t__ nla_len; } ;
struct TYPE_2__ {unsigned int qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  SFQ_ALLOT_SIZE (scalar_t__) ; 
 int SFQ_MAX_DEPTH ; 
 int SFQ_MAX_FLOWS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct red_parms*) ; 
 struct red_parms* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ nla_attr_size (int) ; 
 void* nla_data (struct nlattr*) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  red_check_params (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_set_parms (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 scalar_t__ sfq_drop (struct Qdisc*,struct sk_buff**) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct red_parms*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int sfq_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	struct tc_sfq_qopt *ctl = nla_data(opt);
	struct tc_sfq_qopt_v1 *ctl_v1 = NULL;
	unsigned int qlen, dropped = 0;
	struct red_parms *p = NULL;
	struct sk_buff *to_free = NULL;
	struct sk_buff *tail = NULL;

	if (opt->nla_len < nla_attr_size(sizeof(*ctl)))
		return -EINVAL;
	if (opt->nla_len >= nla_attr_size(sizeof(*ctl_v1)))
		ctl_v1 = nla_data(opt);
	if (ctl->divisor &&
	    (!is_power_of_2(ctl->divisor) || ctl->divisor > 65536))
		return -EINVAL;
	if (ctl_v1 && !red_check_params(ctl_v1->qth_min, ctl_v1->qth_max,
					ctl_v1->Wlog))
		return -EINVAL;
	if (ctl_v1 && ctl_v1->qth_min) {
		p = kmalloc(sizeof(*p), GFP_KERNEL);
		if (!p)
			return -ENOMEM;
	}
	sch_tree_lock(sch);
	if (ctl->quantum) {
		q->quantum = ctl->quantum;
		q->scaled_quantum = SFQ_ALLOT_SIZE(q->quantum);
	}
	q->perturb_period = ctl->perturb_period * HZ;
	if (ctl->flows)
		q->maxflows = min_t(u32, ctl->flows, SFQ_MAX_FLOWS);
	if (ctl->divisor) {
		q->divisor = ctl->divisor;
		q->maxflows = min_t(u32, q->maxflows, q->divisor);
	}
	if (ctl_v1) {
		if (ctl_v1->depth)
			q->maxdepth = min_t(u32, ctl_v1->depth, SFQ_MAX_DEPTH);
		if (p) {
			swap(q->red_parms, p);
			red_set_parms(q->red_parms,
				      ctl_v1->qth_min, ctl_v1->qth_max,
				      ctl_v1->Wlog,
				      ctl_v1->Plog, ctl_v1->Scell_log,
				      NULL,
				      ctl_v1->max_P);
		}
		q->flags = ctl_v1->flags;
		q->headdrop = ctl_v1->headdrop;
	}
	if (ctl->limit) {
		q->limit = min_t(u32, ctl->limit, q->maxdepth * q->maxflows);
		q->maxflows = min_t(u32, q->maxflows, q->limit);
	}

	qlen = sch->q.qlen;
	while (sch->q.qlen > q->limit) {
		dropped += sfq_drop(sch, &to_free);
		if (!tail)
			tail = to_free;
	}

	rtnl_kfree_skbs(to_free, tail);
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen, dropped);

	del_timer(&q->perturb_timer);
	if (q->perturb_period) {
		mod_timer(&q->perturb_timer, jiffies + q->perturb_period);
		get_random_bytes(&q->perturbation, sizeof(q->perturbation));
	}
	sch_tree_unlock(sch);
	kfree(p);
	return 0;
}
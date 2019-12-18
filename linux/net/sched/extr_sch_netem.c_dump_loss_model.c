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
struct tc_netem_gimodel {int /*<<< orphan*/  k1; int /*<<< orphan*/  h; int /*<<< orphan*/  r; int /*<<< orphan*/  p; int /*<<< orphan*/  p23; int /*<<< orphan*/  p14; int /*<<< orphan*/  p32; int /*<<< orphan*/  p31; int /*<<< orphan*/  p13; } ;
struct tc_netem_gemodel {int /*<<< orphan*/  k1; int /*<<< orphan*/  h; int /*<<< orphan*/  r; int /*<<< orphan*/  p; int /*<<< orphan*/  p23; int /*<<< orphan*/  p14; int /*<<< orphan*/  p32; int /*<<< orphan*/  p31; int /*<<< orphan*/  p13; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  a4; int /*<<< orphan*/  a3; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a5; } ;
struct netem_sched_data {int loss_model; TYPE_1__ clg; } ;
typedef  int /*<<< orphan*/  gi ;
typedef  int /*<<< orphan*/  ge ;

/* Variables and functions */
#define  CLG_4_STATES 130 
#define  CLG_GILB_ELL 129 
#define  CLG_RANDOM 128 
 int /*<<< orphan*/  NETEM_LOSS_GE ; 
 int /*<<< orphan*/  NETEM_LOSS_GI ; 
 int /*<<< orphan*/  TCA_NETEM_LOSS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_netem_gimodel*) ; 

__attribute__((used)) static int dump_loss_model(const struct netem_sched_data *q,
			   struct sk_buff *skb)
{
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_NETEM_LOSS);
	if (nest == NULL)
		goto nla_put_failure;

	switch (q->loss_model) {
	case CLG_RANDOM:
		/* legacy loss model */
		nla_nest_cancel(skb, nest);
		return 0;	/* no data */

	case CLG_4_STATES: {
		struct tc_netem_gimodel gi = {
			.p13 = q->clg.a1,
			.p31 = q->clg.a2,
			.p32 = q->clg.a3,
			.p14 = q->clg.a4,
			.p23 = q->clg.a5,
		};

		if (nla_put(skb, NETEM_LOSS_GI, sizeof(gi), &gi))
			goto nla_put_failure;
		break;
	}
	case CLG_GILB_ELL: {
		struct tc_netem_gemodel ge = {
			.p = q->clg.a1,
			.r = q->clg.a2,
			.h = q->clg.a3,
			.k1 = q->clg.a4,
		};

		if (nla_put(skb, NETEM_LOSS_GE, sizeof(ge), &ge))
			goto nla_put_failure;
		break;
	}
	}

	nla_nest_end(skb, nest);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}
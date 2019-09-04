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
struct tc_prio_qopt {int /*<<< orphan*/  priomap; int /*<<< orphan*/  bands; } ;
struct sk_buff {int len; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  PFIFO_FAST_BANDS ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 scalar_t__ TC_PRIO_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_prio_qopt*) ; 
 int /*<<< orphan*/  prio2band ; 

__attribute__((used)) static int pfifo_fast_dump(struct Qdisc *qdisc, struct sk_buff *skb)
{
	struct tc_prio_qopt opt = { .bands = PFIFO_FAST_BANDS };

	memcpy(&opt.priomap, prio2band, TC_PRIO_MAX + 1);
	if (nla_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nla_put_failure;
	return skb->len;

nla_put_failure:
	return -1;
}
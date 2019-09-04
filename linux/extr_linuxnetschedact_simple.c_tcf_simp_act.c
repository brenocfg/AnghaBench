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
struct tcf_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  packets; } ;
struct tcf_defact {int tcf_action; int /*<<< orphan*/  tcf_lock; TYPE_1__ tcf_bstats; scalar_t__ tcfd_defdata; int /*<<< orphan*/  tcf_tm; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstats_update (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 struct tcf_defact* to_defact (struct tc_action const*) ; 

__attribute__((used)) static int tcf_simp_act(struct sk_buff *skb, const struct tc_action *a,
			struct tcf_result *res)
{
	struct tcf_defact *d = to_defact(a);

	spin_lock(&d->tcf_lock);
	tcf_lastuse_update(&d->tcf_tm);
	bstats_update(&d->tcf_bstats, skb);

	/* print policy string followed by _ then packet count
	 * Example if this was the 3rd packet and the string was "hello"
	 * then it would look like "hello_3" (without quotes)
	 */
	pr_info("simple: %s_%d\n",
	       (char *)d->tcfd_defdata, d->tcf_bstats.packets);
	spin_unlock(&d->tcf_lock);
	return d->tcf_action;
}
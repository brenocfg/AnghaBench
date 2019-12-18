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
struct sk_buff {int dummy; } ;
struct rb_node {int dummy; } ;
struct etf_sched_data {int /*<<< orphan*/  head; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct rb_node* rb_first_cached (int /*<<< orphan*/ *) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 

__attribute__((used)) static struct sk_buff *etf_peek_timesortedlist(struct Qdisc *sch)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct rb_node *p;

	p = rb_first_cached(&q->head);
	if (!p)
		return NULL;

	return rb_to_skb(p);
}
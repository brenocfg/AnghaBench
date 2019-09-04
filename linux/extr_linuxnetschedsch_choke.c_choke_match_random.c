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
struct choke_sched_data {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */
 int choke_match_flow (struct sk_buff*,struct sk_buff*) ; 
 struct sk_buff* choke_peek_random (struct choke_sched_data const*,unsigned int*) ; 

__attribute__((used)) static bool choke_match_random(const struct choke_sched_data *q,
			       struct sk_buff *nskb,
			       unsigned int *pidx)
{
	struct sk_buff *oskb;

	if (q->head == q->tail)
		return false;

	oskb = choke_peek_random(q, pidx);
	return choke_match_flow(oskb, nskb);
}
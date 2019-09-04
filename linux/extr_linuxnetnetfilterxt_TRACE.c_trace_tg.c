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
struct xt_action_param {int dummy; } ;
struct sk_buff {int nf_trace; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 

__attribute__((used)) static unsigned int
trace_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	skb->nf_trace = 1;
	return XT_CONTINUE;
}
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
struct cbq_class {int dummy; } ;

/* Variables and functions */
 scalar_t__ cbq_dump_fopt (struct sk_buff*,struct cbq_class*) ; 
 scalar_t__ cbq_dump_lss (struct sk_buff*,struct cbq_class*) ; 
 scalar_t__ cbq_dump_rate (struct sk_buff*,struct cbq_class*) ; 
 scalar_t__ cbq_dump_wrr (struct sk_buff*,struct cbq_class*) ; 

__attribute__((used)) static int cbq_dump_attr(struct sk_buff *skb, struct cbq_class *cl)
{
	if (cbq_dump_lss(skb, cl) < 0 ||
	    cbq_dump_rate(skb, cl) < 0 ||
	    cbq_dump_wrr(skb, cl) < 0 ||
	    cbq_dump_fopt(skb, cl) < 0)
		return -1;
	return 0;
}
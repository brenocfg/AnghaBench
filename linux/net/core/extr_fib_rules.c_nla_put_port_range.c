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
struct fib_rule_port_range {int dummy; } ;

/* Variables and functions */
 int nla_put (struct sk_buff*,int,int,struct fib_rule_port_range*) ; 

__attribute__((used)) static int nla_put_port_range(struct sk_buff *skb, int attrtype,
			      struct fib_rule_port_range *range)
{
	return nla_put(skb, attrtype, sizeof(*range), range);
}
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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ skb_copy_bits (struct sk_buff const*,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int trace_fill_header(struct sk_buff *nlskb, u16 type,
			     const struct sk_buff *skb,
			     int off, unsigned int len)
{
	struct nlattr *nla;

	if (len == 0)
		return 0;

	nla = nla_reserve(nlskb, type, len);
	if (!nla || skb_copy_bits(skb, off, nla_data(nla), len))
		return -1;

	return 0;
}
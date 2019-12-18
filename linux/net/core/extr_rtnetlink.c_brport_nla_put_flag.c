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
typedef  unsigned int u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int nla_put_u8 (struct sk_buff*,unsigned int,int) ; 

__attribute__((used)) static int brport_nla_put_flag(struct sk_buff *skb, u32 flags, u32 mask,
			       unsigned int attrnum, unsigned int flag)
{
	if (mask & flag)
		return nla_put_u8(skb, attrnum, !!(flags & flag));
	return 0;
}
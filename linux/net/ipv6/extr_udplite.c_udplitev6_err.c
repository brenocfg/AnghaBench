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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int __udp6_lib_err (struct sk_buff*,struct inet6_skb_parm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udplite_table ; 

__attribute__((used)) static int udplitev6_err(struct sk_buff *skb,
			  struct inet6_skb_parm *opt,
			  u8 type, u8 code, int offset, __be32 info)
{
	return __udp6_lib_err(skb, opt, type, code, offset, info,
			      &udplite_table);
}
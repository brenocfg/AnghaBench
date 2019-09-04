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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  mem ;

/* Variables and functions */
 int SK_MEMINFO_VARS ; 
 int nla_put (struct sk_buff*,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sk_get_meminfo (struct sock*,int /*<<< orphan*/ *) ; 

int sock_diag_put_meminfo(struct sock *sk, struct sk_buff *skb, int attrtype)
{
	u32 mem[SK_MEMINFO_VARS];

	sk_get_meminfo(sk, mem);

	return nla_put(skb, attrtype, sizeof(mem), &mem);
}
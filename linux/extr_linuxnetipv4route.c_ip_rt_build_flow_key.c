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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_sk_flow_key (struct flowi4*,struct sock const*) ; 
 int /*<<< orphan*/  build_skb_flow_key (struct flowi4*,struct sk_buff const*,struct sock const*) ; 

__attribute__((used)) static void ip_rt_build_flow_key(struct flowi4 *fl4, const struct sock *sk,
				 const struct sk_buff *skb)
{
	if (skb)
		build_skb_flow_key(fl4, skb, sk);
	else
		build_sk_flow_key(fl4, sk);
}
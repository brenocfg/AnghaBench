#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_dst {struct dst_entry* route; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_pmtu ) (struct dst_entry*,struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xfrm6_update_pmtu(struct dst_entry *dst, struct sock *sk,
			      struct sk_buff *skb, u32 mtu)
{
	struct xfrm_dst *xdst = (struct xfrm_dst *)dst;
	struct dst_entry *path = xdst->route;

	path->ops->update_pmtu(path, sk, skb, mtu);
}
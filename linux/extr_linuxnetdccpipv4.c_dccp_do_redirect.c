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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* redirect ) (struct dst_entry*,struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void dccp_do_redirect(struct sk_buff *skb, struct sock *sk)
{
	struct dst_entry *dst = __sk_dst_check(sk, 0);

	if (dst)
		dst->ops->redirect(dst, sk, skb);
}
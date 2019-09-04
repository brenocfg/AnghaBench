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
struct sctp_transport {int dummy; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* redirect ) (struct dst_entry*,struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 struct dst_entry* sctp_transport_dst_check (struct sctp_transport*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct sock*,struct sk_buff*) ; 

void sctp_icmp_redirect(struct sock *sk, struct sctp_transport *t,
			struct sk_buff *skb)
{
	struct dst_entry *dst;

	if (sock_owned_by_user(sk) || !t)
		return;
	dst = sctp_transport_dst_check(t);
	if (dst)
		dst->ops->redirect(dst, sk, skb);
}
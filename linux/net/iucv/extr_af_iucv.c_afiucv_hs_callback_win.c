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
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct iucv_sock {int /*<<< orphan*/  msg_sent; } ;
struct TYPE_2__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 scalar_t__ IUCV_CONNECTED ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_wake_msglim (struct sock*) ; 
 TYPE_1__* iucv_trans_hdr (struct sk_buff*) ; 

__attribute__((used)) static int afiucv_hs_callback_win(struct sock *sk, struct sk_buff *skb)
{
	struct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv)
		return NET_RX_SUCCESS;

	if (sk->sk_state != IUCV_CONNECTED)
		return NET_RX_SUCCESS;

	atomic_sub(iucv_trans_hdr(skb)->window, &iucv->msg_sent);
	iucv_sock_wake_msglim(sk);
	return NET_RX_SUCCESS;
}
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
struct sock {int /*<<< orphan*/  sk_callback_lock; TYPE_1__* sk_socket; } ;
struct TYPE_2__ {scalar_t__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 scalar_t__ file_ns_capable (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ sysctl_tstamp_allow_data ; 

__attribute__((used)) static bool skb_may_tx_timestamp(struct sock *sk, bool tsonly)
{
	bool ret;

	if (likely(sysctl_tstamp_allow_data || tsonly))
		return true;

	read_lock_bh(&sk->sk_callback_lock);
	ret = sk->sk_socket && sk->sk_socket->file &&
	      file_ns_capable(sk->sk_socket->file, &init_user_ns, CAP_NET_RAW);
	read_unlock_bh(&sk->sk_callback_lock);
	return ret;
}
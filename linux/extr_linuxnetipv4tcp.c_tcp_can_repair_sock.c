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
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sock_net (struct sock const*) ; 

__attribute__((used)) static inline bool tcp_can_repair_sock(const struct sock *sk)
{
	return ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN) &&
		(sk->sk_state != TCP_LISTEN);
}
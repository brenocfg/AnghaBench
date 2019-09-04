#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {TYPE_1__* sk_prot; } ;
struct TYPE_4__ {int /*<<< orphan*/  inet_num; } ;
struct TYPE_3__ {int (* disconnect ) (struct sock*,int) ;int (* pre_connect ) (struct sock*,struct sockaddr*,int) ;int (* connect ) (struct sock*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 scalar_t__ BPF_CGROUP_PRE_CONNECT_ENABLED (struct sock*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ inet_autobind (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int stub1 (struct sock*,int) ; 
 int stub2 (struct sock*,struct sockaddr*,int) ; 
 int stub3 (struct sock*,struct sockaddr*,int) ; 

int inet_dgram_connect(struct socket *sock, struct sockaddr *uaddr,
		       int addr_len, int flags)
{
	struct sock *sk = sock->sk;
	int err;

	if (addr_len < sizeof(uaddr->sa_family))
		return -EINVAL;
	if (uaddr->sa_family == AF_UNSPEC)
		return sk->sk_prot->disconnect(sk, flags);

	if (BPF_CGROUP_PRE_CONNECT_ENABLED(sk)) {
		err = sk->sk_prot->pre_connect(sk, uaddr, addr_len);
		if (err)
			return err;
	}

	if (!inet_sk(sk)->inet_num && inet_autobind(sk))
		return -EAGAIN;
	return sk->sk_prot->connect(sk, uaddr, addr_len);
}
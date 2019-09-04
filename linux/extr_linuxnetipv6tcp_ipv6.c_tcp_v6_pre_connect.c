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
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int BPF_CGROUP_RUN_PROG_INET6_CONNECT (struct sock*,struct sockaddr*) ; 
 int EINVAL ; 
 int SIN6_LEN_RFC2133 ; 
 int /*<<< orphan*/  sock_owned_by_me (struct sock*) ; 

__attribute__((used)) static int tcp_v6_pre_connect(struct sock *sk, struct sockaddr *uaddr,
			      int addr_len)
{
	/* This check is replicated from tcp_v6_connect() and intended to
	 * prevent BPF program called below from accessing bytes that are out
	 * of the bound specified by user in addr_len.
	 */
	if (addr_len < SIN6_LEN_RFC2133)
		return -EINVAL;

	sock_owned_by_me(sk);

	return BPF_CGROUP_RUN_PROG_INET6_CONNECT(sk, uaddr);
}
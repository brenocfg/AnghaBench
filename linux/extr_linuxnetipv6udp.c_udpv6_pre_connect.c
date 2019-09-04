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
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int BPF_CGROUP_RUN_PROG_INET6_CONNECT_LOCK (struct sock*,struct sockaddr*) ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int SIN6_LEN_RFC2133 ; 
 scalar_t__ __ipv6_only_sock (struct sock*) ; 
 int udp_pre_connect (struct sock*,struct sockaddr*,int) ; 

__attribute__((used)) static int udpv6_pre_connect(struct sock *sk, struct sockaddr *uaddr,
			     int addr_len)
{
	/* The following checks are replicated from __ip6_datagram_connect()
	 * and intended to prevent BPF program called below from accessing
	 * bytes that are out of the bound specified by user in addr_len.
	 */
	if (uaddr->sa_family == AF_INET) {
		if (__ipv6_only_sock(sk))
			return -EAFNOSUPPORT;
		return udp_pre_connect(sk, uaddr, addr_len);
	}

	if (addr_len < SIN6_LEN_RFC2133)
		return -EINVAL;

	return BPF_CGROUP_RUN_PROG_INET6_CONNECT_LOCK(sk, uaddr);
}
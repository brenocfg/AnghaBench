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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_userlocks; TYPE_2__* sk_prot; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct inet_sock {scalar_t__ inet_rcv_saddr; scalar_t__ inet_saddr; scalar_t__ inet_dport; scalar_t__ inet_daddr; scalar_t__ inet_num; int /*<<< orphan*/  inet_sport; scalar_t__ bind_address_no_port; } ;
struct TYPE_4__ {scalar_t__ (* get_port ) (struct sock*,unsigned short) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_UNSPEC ; 
 int BPF_CGROUP_RUN_PROG_INET4_POST_BIND (struct sock*) ; 
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int RTN_BROADCAST ; 
 int RTN_LOCAL ; 
 int RTN_MULTICAST ; 
 int /*<<< orphan*/  RT_TABLE_LOCAL ; 
 int /*<<< orphan*/  SOCK_BINDADDR_LOCK ; 
 int /*<<< orphan*/  SOCK_BINDPORT_LOCK ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int inet_addr_type_table (struct net*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_can_nonlocal_bind (struct net*,struct inet_sock*) ; 
 unsigned short inet_prot_sock (struct net*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ l3mdev_fib_table_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 scalar_t__ stub1 (struct sock*,unsigned short) ; 

int __inet_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len,
		bool force_bind_address_no_port, bool with_lock)
{
	struct sockaddr_in *addr = (struct sockaddr_in *)uaddr;
	struct inet_sock *inet = inet_sk(sk);
	struct net *net = sock_net(sk);
	unsigned short snum;
	int chk_addr_ret;
	u32 tb_id = RT_TABLE_LOCAL;
	int err;

	if (addr->sin_family != AF_INET) {
		/* Compatibility games : accept AF_UNSPEC (mapped to AF_INET)
		 * only if s_addr is INADDR_ANY.
		 */
		err = -EAFNOSUPPORT;
		if (addr->sin_family != AF_UNSPEC ||
		    addr->sin_addr.s_addr != htonl(INADDR_ANY))
			goto out;
	}

	tb_id = l3mdev_fib_table_by_index(net, sk->sk_bound_dev_if) ? : tb_id;
	chk_addr_ret = inet_addr_type_table(net, addr->sin_addr.s_addr, tb_id);

	/* Not specified by any standard per-se, however it breaks too
	 * many applications when removed.  It is unfortunate since
	 * allowing applications to make a non-local bind solves
	 * several problems with systems using dynamic addressing.
	 * (ie. your servers still start up even if your ISDN link
	 *  is temporarily down)
	 */
	err = -EADDRNOTAVAIL;
	if (!inet_can_nonlocal_bind(net, inet) &&
	    addr->sin_addr.s_addr != htonl(INADDR_ANY) &&
	    chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST &&
	    chk_addr_ret != RTN_BROADCAST)
		goto out;

	snum = ntohs(addr->sin_port);
	err = -EACCES;
	if (snum && snum < inet_prot_sock(net) &&
	    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
		goto out;

	/*      We keep a pair of addresses. rcv_saddr is the one
	 *      used by hash lookups, and saddr is used for transmit.
	 *
	 *      In the BSD API these are the same except where it
	 *      would be illegal to use them (multicast/broadcast) in
	 *      which case the sending device address is used.
	 */
	if (with_lock)
		lock_sock(sk);

	/* Check these errors (active socket, double bind). */
	err = -EINVAL;
	if (sk->sk_state != TCP_CLOSE || inet->inet_num)
		goto out_release_sock;

	inet->inet_rcv_saddr = inet->inet_saddr = addr->sin_addr.s_addr;
	if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */

	/* Make sure we are allowed to bind here. */
	if (snum || !(inet->bind_address_no_port ||
		      force_bind_address_no_port)) {
		if (sk->sk_prot->get_port(sk, snum)) {
			inet->inet_saddr = inet->inet_rcv_saddr = 0;
			err = -EADDRINUSE;
			goto out_release_sock;
		}
		err = BPF_CGROUP_RUN_PROG_INET4_POST_BIND(sk);
		if (err) {
			inet->inet_saddr = inet->inet_rcv_saddr = 0;
			goto out_release_sock;
		}
	}

	if (inet->inet_rcv_saddr)
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
	if (snum)
		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
	inet->inet_sport = htons(inet->inet_num);
	inet->inet_daddr = 0;
	inet->inet_dport = 0;
	sk_dst_reset(sk);
	err = 0;
out_release_sock:
	if (with_lock)
		release_sock(sk);
out:
	return err;
}
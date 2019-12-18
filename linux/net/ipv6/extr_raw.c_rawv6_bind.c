#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_scope_id; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_v6_rcv_saddr; scalar_t__ sk_bound_dev_if; } ;
struct net_device {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  saddr; } ;
struct inet_sock {int /*<<< orphan*/  inet_saddr; int /*<<< orphan*/  inet_rcv_saddr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  ip_nonlocal_bind; } ;
struct TYPE_7__ {TYPE_1__ sysctl; } ;
struct TYPE_8__ {TYPE_2__ ipv6; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_MULTICAST ; 
 int /*<<< orphan*/  LOOPBACK4_IPV6 ; 
 int SIN6_LEN_RFC2133 ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ __ipv6_addr_needs_scope_id (int) ; 
 struct net_device* dev_get_by_index_rcu (TYPE_3__*,scalar_t__) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_chk_addr (TYPE_3__*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 TYPE_3__* sock_net (struct sock*) ; 

__attribute__((used)) static int rawv6_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sockaddr_in6 *addr = (struct sockaddr_in6 *) uaddr;
	__be32 v4addr = 0;
	int addr_type;
	int err;

	if (addr_len < SIN6_LEN_RFC2133)
		return -EINVAL;

	if (addr->sin6_family != AF_INET6)
		return -EINVAL;

	addr_type = ipv6_addr_type(&addr->sin6_addr);

	/* Raw sockets are IPv6 only */
	if (addr_type == IPV6_ADDR_MAPPED)
		return -EADDRNOTAVAIL;

	lock_sock(sk);

	err = -EINVAL;
	if (sk->sk_state != TCP_CLOSE)
		goto out;

	rcu_read_lock();
	/* Check if the address belongs to the host. */
	if (addr_type != IPV6_ADDR_ANY) {
		struct net_device *dev = NULL;

		if (__ipv6_addr_needs_scope_id(addr_type)) {
			if (addr_len >= sizeof(struct sockaddr_in6) &&
			    addr->sin6_scope_id) {
				/* Override any existing binding, if another
				 * one is supplied by user.
				 */
				sk->sk_bound_dev_if = addr->sin6_scope_id;
			}

			/* Binding to link-local address requires an interface */
			if (!sk->sk_bound_dev_if)
				goto out_unlock;
		}

		if (sk->sk_bound_dev_if) {
			err = -ENODEV;
			dev = dev_get_by_index_rcu(sock_net(sk),
						   sk->sk_bound_dev_if);
			if (!dev)
				goto out_unlock;
		}

		/* ipv4 addr of the socket is invalid.  Only the
		 * unspecified and mapped address have a v4 equivalent.
		 */
		v4addr = LOOPBACK4_IPV6;
		if (!(addr_type & IPV6_ADDR_MULTICAST) &&
		    !sock_net(sk)->ipv6.sysctl.ip_nonlocal_bind) {
			err = -EADDRNOTAVAIL;
			if (!ipv6_chk_addr(sock_net(sk), &addr->sin6_addr,
					   dev, 0)) {
				goto out_unlock;
			}
		}
	}

	inet->inet_rcv_saddr = inet->inet_saddr = v4addr;
	sk->sk_v6_rcv_saddr = addr->sin6_addr;
	if (!(addr_type & IPV6_ADDR_MULTICAST))
		np->saddr = addr->sin6_addr;
	err = 0;
out_unlock:
	rcu_read_unlock();
out:
	release_sock(sk);
	return err;
}
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
struct socket {struct sock* sk; } ;
struct sockaddr_nl {scalar_t__ nl_groups; scalar_t__ nl_pid; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct netlink_sock {scalar_t__ dst_group; scalar_t__ dst_portid; int /*<<< orphan*/  bound; } ;

/* Variables and functions */
 scalar_t__ AF_NETLINK ; 
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  NETLINK_CONNECTED ; 
 int /*<<< orphan*/  NETLINK_UNCONNECTED ; 
 int /*<<< orphan*/  NL_CFG_F_NONROOT_SEND ; 
 scalar_t__ ffs (scalar_t__) ; 
 int /*<<< orphan*/  netlink_allowed (struct socket*,int /*<<< orphan*/ ) ; 
 int netlink_autobind (struct socket*) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 

__attribute__((used)) static int netlink_connect(struct socket *sock, struct sockaddr *addr,
			   int alen, int flags)
{
	int err = 0;
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sockaddr_nl *nladdr = (struct sockaddr_nl *)addr;

	if (alen < sizeof(addr->sa_family))
		return -EINVAL;

	if (addr->sa_family == AF_UNSPEC) {
		sk->sk_state	= NETLINK_UNCONNECTED;
		nlk->dst_portid	= 0;
		nlk->dst_group  = 0;
		return 0;
	}
	if (addr->sa_family != AF_NETLINK)
		return -EINVAL;

	if (alen < sizeof(struct sockaddr_nl))
		return -EINVAL;

	if ((nladdr->nl_groups || nladdr->nl_pid) &&
	    !netlink_allowed(sock, NL_CFG_F_NONROOT_SEND))
		return -EPERM;

	/* No need for barriers here as we return to user-space without
	 * using any of the bound attributes.
	 */
	if (!nlk->bound)
		err = netlink_autobind(sock);

	if (err == 0) {
		sk->sk_state	= NETLINK_CONNECTED;
		nlk->dst_portid = nladdr->nl_pid;
		nlk->dst_group  = ffs(nladdr->nl_groups);
	}

	return err;
}
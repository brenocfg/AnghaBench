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
typedef  int /*<<< orphan*/  u32 ;
struct socket {struct sock* sk; } ;
struct sockaddr_nl {scalar_t__ nl_family; unsigned long nl_groups; scalar_t__ nl_pid; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct netlink_sock {unsigned long ngroups; int bound; scalar_t__ portid; int (* netlink_bind ) (struct net*,int) ;unsigned long* groups; scalar_t__ subscriptions; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_NETLINK ; 
 unsigned long BITS_PER_LONG ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  NL_CFG_F_NONROOT_RECV ; 
 scalar_t__ hweight32 (unsigned long) ; 
 int /*<<< orphan*/  netlink_allowed (struct socket*,int /*<<< orphan*/ ) ; 
 int netlink_autobind (struct socket*) ; 
 int netlink_insert (struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  netlink_lock_table () ; 
 int netlink_realloc_groups (struct sock*) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 int /*<<< orphan*/  netlink_undo_bind (int,unsigned long,struct sock*) ; 
 int /*<<< orphan*/  netlink_unlock_table () ; 
 int /*<<< orphan*/  netlink_update_listeners (struct sock*) ; 
 int /*<<< orphan*/  netlink_update_subscriptions (struct sock*,scalar_t__) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct net* sock_net (struct sock*) ; 
 int stub1 (struct net*,int) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int netlink_bind(struct socket *sock, struct sockaddr *addr,
			int addr_len)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sockaddr_nl *nladdr = (struct sockaddr_nl *)addr;
	int err = 0;
	unsigned long groups;
	bool bound;

	if (addr_len < sizeof(struct sockaddr_nl))
		return -EINVAL;

	if (nladdr->nl_family != AF_NETLINK)
		return -EINVAL;
	groups = nladdr->nl_groups;

	/* Only superuser is allowed to listen multicasts */
	if (groups) {
		if (!netlink_allowed(sock, NL_CFG_F_NONROOT_RECV))
			return -EPERM;
		err = netlink_realloc_groups(sk);
		if (err)
			return err;
	}

	if (nlk->ngroups < BITS_PER_LONG)
		groups &= (1UL << nlk->ngroups) - 1;

	bound = nlk->bound;
	if (bound) {
		/* Ensure nlk->portid is up-to-date. */
		smp_rmb();

		if (nladdr->nl_pid != nlk->portid)
			return -EINVAL;
	}

	netlink_lock_table();
	if (nlk->netlink_bind && groups) {
		int group;

		for (group = 0; group < nlk->ngroups; group++) {
			if (!test_bit(group, &groups))
				continue;
			err = nlk->netlink_bind(net, group + 1);
			if (!err)
				continue;
			netlink_undo_bind(group, groups, sk);
			goto unlock;
		}
	}

	/* No need for barriers here as we return to user-space without
	 * using any of the bound attributes.
	 */
	if (!bound) {
		err = nladdr->nl_pid ?
			netlink_insert(sk, nladdr->nl_pid) :
			netlink_autobind(sock);
		if (err) {
			netlink_undo_bind(nlk->ngroups, groups, sk);
			goto unlock;
		}
	}

	if (!groups && (nlk->groups == NULL || !(u32)nlk->groups[0]))
		goto unlock;
	netlink_unlock_table();

	netlink_table_grab();
	netlink_update_subscriptions(sk, nlk->subscriptions +
					 hweight32(groups) -
					 hweight32(nlk->groups[0]));
	nlk->groups[0] = (nlk->groups[0] & ~0xffffffffUL) | groups;
	netlink_update_listeners(sk);
	netlink_table_ungrab();

	return 0;

unlock:
	netlink_unlock_table();
	return err;
}
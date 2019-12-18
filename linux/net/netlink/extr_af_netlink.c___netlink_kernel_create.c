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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_data_ready; } ;
struct netlink_sock {int /*<<< orphan*/  flags; scalar_t__ netlink_rcv; } ;
struct netlink_kernel_cfg {int groups; scalar_t__ compare; int /*<<< orphan*/  flags; int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; scalar_t__ input; struct mutex* cb_mutex; } ;
struct net {int dummy; } ;
struct mutex {int dummy; } ;
struct module {int dummy; } ;
struct listeners {int dummy; } ;
struct TYPE_2__ {int registered; unsigned int groups; scalar_t__ compare; int /*<<< orphan*/  flags; int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; struct module* module; struct mutex* cb_mutex; int /*<<< orphan*/  listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_LINKS ; 
 int /*<<< orphan*/  NETLINK_F_KERNEL_SOCKET ; 
 scalar_t__ NLGRPSZ (unsigned int) ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ __netlink_create (struct net*,struct socket*,struct mutex*,int,int) ; 
 int /*<<< orphan*/  kfree (struct listeners*) ; 
 struct listeners* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_data_ready ; 
 scalar_t__ netlink_insert (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_kernel_release (struct sock*) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct listeners*) ; 
 scalar_t__ sock_create_lite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

struct sock *
__netlink_kernel_create(struct net *net, int unit, struct module *module,
			struct netlink_kernel_cfg *cfg)
{
	struct socket *sock;
	struct sock *sk;
	struct netlink_sock *nlk;
	struct listeners *listeners = NULL;
	struct mutex *cb_mutex = cfg ? cfg->cb_mutex : NULL;
	unsigned int groups;

	BUG_ON(!nl_table);

	if (unit < 0 || unit >= MAX_LINKS)
		return NULL;

	if (sock_create_lite(PF_NETLINK, SOCK_DGRAM, unit, &sock))
		return NULL;

	if (__netlink_create(net, sock, cb_mutex, unit, 1) < 0)
		goto out_sock_release_nosk;

	sk = sock->sk;

	if (!cfg || cfg->groups < 32)
		groups = 32;
	else
		groups = cfg->groups;

	listeners = kzalloc(sizeof(*listeners) + NLGRPSZ(groups), GFP_KERNEL);
	if (!listeners)
		goto out_sock_release;

	sk->sk_data_ready = netlink_data_ready;
	if (cfg && cfg->input)
		nlk_sk(sk)->netlink_rcv = cfg->input;

	if (netlink_insert(sk, 0))
		goto out_sock_release;

	nlk = nlk_sk(sk);
	nlk->flags |= NETLINK_F_KERNEL_SOCKET;

	netlink_table_grab();
	if (!nl_table[unit].registered) {
		nl_table[unit].groups = groups;
		rcu_assign_pointer(nl_table[unit].listeners, listeners);
		nl_table[unit].cb_mutex = cb_mutex;
		nl_table[unit].module = module;
		if (cfg) {
			nl_table[unit].bind = cfg->bind;
			nl_table[unit].unbind = cfg->unbind;
			nl_table[unit].flags = cfg->flags;
			if (cfg->compare)
				nl_table[unit].compare = cfg->compare;
		}
		nl_table[unit].registered = 1;
	} else {
		kfree(listeners);
		nl_table[unit].registered++;
	}
	netlink_table_ungrab();
	return sk;

out_sock_release:
	kfree(listeners);
	netlink_kernel_release(sk);
	return NULL;

out_sock_release_nosk:
	sock_release(sock);
	return NULL;
}
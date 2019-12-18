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
struct sock {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 struct net* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct net* get_net_ns_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int /*<<< orphan*/  sk_ns_capable (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

struct net *rtnl_get_net_ns_capable(struct sock *sk, int netnsid)
{
	struct net *net;

	net = get_net_ns_by_id(sock_net(sk), netnsid);
	if (!net)
		return ERR_PTR(-EINVAL);

	/* For now, the caller is required to have CAP_NET_ADMIN in
	 * the user namespace owning the target net ns.
	 */
	if (!sk_ns_capable(sk, net->user_ns, CAP_NET_ADMIN)) {
		put_net(net);
		return ERR_PTR(-EACCES);
	}
	return net;
}
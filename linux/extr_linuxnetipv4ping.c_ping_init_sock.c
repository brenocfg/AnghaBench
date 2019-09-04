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
struct sock {scalar_t__ sk_family; int sk_ipv6only; } ;
struct net {int dummy; } ;
struct group_info {int ngroups; int /*<<< orphan*/ * gid; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EACCES ; 
 int /*<<< orphan*/  current_egid () ; 
 struct group_info* get_current_groups () ; 
 scalar_t__ gid_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_get_ping_group_range_net (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_group_info (struct group_info*) ; 
 struct net* sock_net (struct sock*) ; 

int ping_init_sock(struct sock *sk)
{
	struct net *net = sock_net(sk);
	kgid_t group = current_egid();
	struct group_info *group_info;
	int i;
	kgid_t low, high;
	int ret = 0;

	if (sk->sk_family == AF_INET6)
		sk->sk_ipv6only = 1;

	inet_get_ping_group_range_net(net, &low, &high);
	if (gid_lte(low, group) && gid_lte(group, high))
		return 0;

	group_info = get_current_groups();
	for (i = 0; i < group_info->ngroups; i++) {
		kgid_t gid = group_info->gid[i];

		if (gid_lte(low, gid) && gid_lte(gid, high))
			goto out_release_group;
	}

	ret = -EACCES;

out_release_group:
	put_group_info(group_info);
	return ret;
}
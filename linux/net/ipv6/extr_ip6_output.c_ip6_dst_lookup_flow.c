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
struct in6_addr {int dummy; } ;
struct flowi6 {struct in6_addr daddr; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int ip6_dst_lookup_tail (int /*<<< orphan*/ ,struct sock const*,struct dst_entry**,struct flowi6*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 struct dst_entry* xfrm_lookup_route (int /*<<< orphan*/ ,struct dst_entry*,int /*<<< orphan*/ ,struct sock const*,int /*<<< orphan*/ ) ; 

struct dst_entry *ip6_dst_lookup_flow(const struct sock *sk, struct flowi6 *fl6,
				      const struct in6_addr *final_dst)
{
	struct dst_entry *dst = NULL;
	int err;

	err = ip6_dst_lookup_tail(sock_net(sk), sk, &dst, fl6);
	if (err)
		return ERR_PTR(err);
	if (final_dst)
		fl6->daddr = *final_dst;

	return xfrm_lookup_route(sock_net(sk), dst, flowi6_to_flowi(fl6), sk, 0);
}
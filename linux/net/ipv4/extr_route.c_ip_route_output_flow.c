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
struct rtable {int /*<<< orphan*/  dst; } ;
struct net {int dummy; } ;
struct flowi4 {scalar_t__ flowi4_proto; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtable*) ; 
 struct rtable* __ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 scalar_t__ xfrm_lookup_route (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sock const*,int /*<<< orphan*/ ) ; 

struct rtable *ip_route_output_flow(struct net *net, struct flowi4 *flp4,
				    const struct sock *sk)
{
	struct rtable *rt = __ip_route_output_key(net, flp4);

	if (IS_ERR(rt))
		return rt;

	if (flp4->flowi4_proto)
		rt = (struct rtable *)xfrm_lookup_route(net, &rt->dst,
							flowi4_to_flowi(flp4),
							sk, 0);

	return rt;
}
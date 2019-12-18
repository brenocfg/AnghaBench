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
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_policy_afinfo {struct dst_entry* (* blackhole_route ) (struct net*,struct dst_entry*) ;} ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dst_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* stub1 (struct net*,struct dst_entry*) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dst_entry *make_blackhole(struct net *net, u16 family,
					struct dst_entry *dst_orig)
{
	const struct xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);
	struct dst_entry *ret;

	if (!afinfo) {
		dst_release(dst_orig);
		return ERR_PTR(-EINVAL);
	} else {
		ret = afinfo->blackhole_route(net, dst_orig);
	}
	rcu_read_unlock();

	return ret;
}
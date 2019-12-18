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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_policy_afinfo {struct dst_entry* (* dst_lookup ) (struct net*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct dst_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* stub1 (struct net*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int) ; 

struct dst_entry *__xfrm_dst_lookup(struct net *net, int tos, int oif,
				    const xfrm_address_t *saddr,
				    const xfrm_address_t *daddr,
				    int family, u32 mark)
{
	const struct xfrm_policy_afinfo *afinfo;
	struct dst_entry *dst;

	afinfo = xfrm_policy_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return ERR_PTR(-EAFNOSUPPORT);

	dst = afinfo->dst_lookup(net, tos, oif, saddr, daddr, mark);

	rcu_read_unlock();

	return dst;
}
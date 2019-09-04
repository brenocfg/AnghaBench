#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  xfrm_policy_lock; TYPE_1__* policy_bydst; } ;
struct net {TYPE_2__ xfrm; } ;
struct hlist_head {int dummy; } ;
struct TYPE_3__ {unsigned int hmask; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 unsigned int __addr_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned short,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_hash_thresh (struct net*,unsigned short,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct hlist_head* rcu_dereference_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *policy_hash_direct(struct net *net,
					     const xfrm_address_t *daddr,
					     const xfrm_address_t *saddr,
					     unsigned short family, int dir)
{
	unsigned int hmask = net->xfrm.policy_bydst[dir].hmask;
	unsigned int hash;
	u8 dbits;
	u8 sbits;

	__get_hash_thresh(net, family, dir, &dbits, &sbits);
	hash = __addr_hash(daddr, saddr, family, hmask, dbits, sbits);

	return rcu_dereference_check(net->xfrm.policy_bydst[dir].table,
		     lockdep_is_held(&net->xfrm.xfrm_policy_lock)) + hash;
}
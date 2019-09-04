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
struct net_device {int /*<<< orphan*/  name; } ;
struct ip_vs_dest_dst {TYPE_1__* dst_cache; } ;
struct ip_vs_dest {int /*<<< orphan*/  dst_lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; int /*<<< orphan*/  dest_dst; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ip_vs_dst_cache_reset (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct ip_vs_dest_dst* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ip_vs_forget_dev(struct ip_vs_dest *dest, struct net_device *dev)
{
	struct ip_vs_dest_dst *dest_dst;

	spin_lock_bh(&dest->dst_lock);
	dest_dst = rcu_dereference_protected(dest->dest_dst, 1);
	if (dest_dst && dest_dst->dst_cache->dev == dev) {
		IP_VS_DBG_BUF(3, "Reset dev:%s dest %s:%u ,dest->refcnt=%d\n",
			      dev->name,
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port),
			      refcount_read(&dest->refcnt));
		__ip_vs_dst_cache_reset(dest);
	}
	spin_unlock_bh(&dest->dst_lock);

}
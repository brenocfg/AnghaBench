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
struct net {int dummy; } ;
struct clusterip_config {int /*<<< orphan*/  entries; int /*<<< orphan*/  refcount; int /*<<< orphan*/  pde; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct clusterip_config* __clusterip_config_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_config_put (struct clusterip_config*) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct clusterip_config *
clusterip_config_find_get(struct net *net, __be32 clusterip, int entry)
{
	struct clusterip_config *c;

	rcu_read_lock_bh();
	c = __clusterip_config_find(net, clusterip);
	if (c) {
#ifdef CONFIG_PROC_FS
		if (!c->pde)
			c = NULL;
		else
#endif
		if (unlikely(!refcount_inc_not_zero(&c->refcount)))
			c = NULL;
		else if (entry) {
			if (unlikely(!refcount_inc_not_zero(&c->entries))) {
				clusterip_config_put(c);
				c = NULL;
			}
		}
	}
	rcu_read_unlock_bh();

	return c;
}
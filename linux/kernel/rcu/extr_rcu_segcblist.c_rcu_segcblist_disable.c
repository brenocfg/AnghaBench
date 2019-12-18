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
struct rcu_segcblist {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  rcu_segcblist_empty (struct rcu_segcblist*) ; 
 int rcu_segcblist_n_cbs (struct rcu_segcblist*) ; 
 int rcu_segcblist_n_lazy_cbs (struct rcu_segcblist*) ; 

void rcu_segcblist_disable(struct rcu_segcblist *rsclp)
{
	WARN_ON_ONCE(!rcu_segcblist_empty(rsclp));
	WARN_ON_ONCE(rcu_segcblist_n_cbs(rsclp));
	WARN_ON_ONCE(rcu_segcblist_n_lazy_cbs(rsclp));
	rsclp->enabled = 0;
}
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
struct rcu_segcblist {scalar_t__ len_lazy; } ;
struct rcu_cblist {int /*<<< orphan*/  len; int /*<<< orphan*/  len_lazy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_segcblist_xchg_len (struct rcu_segcblist*,int /*<<< orphan*/ ) ; 

void rcu_segcblist_extract_count(struct rcu_segcblist *rsclp,
					       struct rcu_cblist *rclp)
{
	rclp->len_lazy += rsclp->len_lazy;
	rsclp->len_lazy = 0;
	rclp->len = rcu_segcblist_xchg_len(rsclp, 0);
}
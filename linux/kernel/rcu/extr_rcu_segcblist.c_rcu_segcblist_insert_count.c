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
struct rcu_segcblist {int /*<<< orphan*/  len_lazy; } ;
struct rcu_cblist {scalar_t__ len; scalar_t__ len_lazy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_segcblist_add_len (struct rcu_segcblist*,scalar_t__) ; 

void rcu_segcblist_insert_count(struct rcu_segcblist *rsclp,
				struct rcu_cblist *rclp)
{
	rsclp->len_lazy += rclp->len_lazy;
	rcu_segcblist_add_len(rsclp, rclp->len);
	rclp->len_lazy = 0;
	rclp->len = 0;
}
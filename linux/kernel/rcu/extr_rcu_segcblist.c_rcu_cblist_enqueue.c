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
struct rcu_head {struct rcu_head* next; } ;
struct rcu_cblist {scalar_t__ len; struct rcu_head** tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 

void rcu_cblist_enqueue(struct rcu_cblist *rclp, struct rcu_head *rhp)
{
	*rclp->tail = rhp;
	rclp->tail = &rhp->next;
	WRITE_ONCE(rclp->len, rclp->len + 1);
}
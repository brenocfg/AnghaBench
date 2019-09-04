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
struct rcu_cblist {struct rcu_head* head; struct rcu_head** tail; int /*<<< orphan*/  len; } ;

/* Variables and functions */

struct rcu_head *rcu_cblist_dequeue(struct rcu_cblist *rclp)
{
	struct rcu_head *rhp;

	rhp = rclp->head;
	if (!rhp)
		return NULL;
	rclp->len--;
	rclp->head = rhp->next;
	if (!rclp->head)
		rclp->tail = &rclp->head;
	return rhp;
}
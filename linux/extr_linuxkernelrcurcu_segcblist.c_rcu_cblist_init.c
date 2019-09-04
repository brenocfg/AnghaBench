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
struct rcu_cblist {scalar_t__ len_lazy; scalar_t__ len; int /*<<< orphan*/ * head; int /*<<< orphan*/ ** tail; } ;

/* Variables and functions */

void rcu_cblist_init(struct rcu_cblist *rclp)
{
	rclp->head = NULL;
	rclp->tail = &rclp->head;
	rclp->len = 0;
	rclp->len_lazy = 0;
}
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
struct rcu_segcblist {struct rcu_head* head; } ;
struct rcu_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct rcu_head *rcu_segcblist_head(struct rcu_segcblist *rsclp)
{
	return rsclp->head;
}
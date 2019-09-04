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
struct Qdisc {scalar_t__ parent; int flags; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int TCQ_F_INGRESS ; 
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 

void qdisc_hash_del(struct Qdisc *q)
{
	if ((q->parent != TC_H_ROOT) && !(q->flags & TCQ_F_INGRESS)) {
		ASSERT_RTNL();
		hash_del_rcu(&q->hash);
	}
}
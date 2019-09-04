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
struct Qdisc {scalar_t__ parent; int flags; int /*<<< orphan*/  handle; int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {int /*<<< orphan*/  qdisc_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int TCQ_F_INGRESS ; 
 int TCQ_F_INVISIBLE ; 
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 

void qdisc_hash_add(struct Qdisc *q, bool invisible)
{
	if ((q->parent != TC_H_ROOT) && !(q->flags & TCQ_F_INGRESS)) {
		ASSERT_RTNL();
		hash_add_rcu(qdisc_dev(q)->qdisc_hash, &q->hash, q->handle);
		if (invisible)
			q->flags |= TCQ_F_INVISIBLE;
	}
}
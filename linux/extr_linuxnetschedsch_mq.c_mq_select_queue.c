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
struct tcmsg {int /*<<< orphan*/  tcm_parent; } ;
struct netdev_queue {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct netdev_queue* mq_queue_get (struct Qdisc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netdev_queue *mq_select_queue(struct Qdisc *sch,
					    struct tcmsg *tcm)
{
	return mq_queue_get(sch, TC_H_MIN(tcm->tcm_parent));
}
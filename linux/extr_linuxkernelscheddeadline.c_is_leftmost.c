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
struct sched_dl_entity {int /*<<< orphan*/  rb_node; } ;
struct task_struct {struct sched_dl_entity dl; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rb_leftmost; } ;
struct dl_rq {TYPE_1__ root; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_leftmost(struct task_struct *p, struct dl_rq *dl_rq)
{
	struct sched_dl_entity *dl_se = &p->dl;

	return dl_rq->root.rb_leftmost == &dl_se->rb_node;
}
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
struct sched_dl_entity {int /*<<< orphan*/  rb_node; } ;
struct dl_rq {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dec_dl_tasks (struct sched_dl_entity*,struct dl_rq*) ; 
 struct dl_rq* dl_rq_of_se (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dequeue_dl_entity(struct sched_dl_entity *dl_se)
{
	struct dl_rq *dl_rq = dl_rq_of_se(dl_se);

	if (RB_EMPTY_NODE(&dl_se->rb_node))
		return;

	rb_erase_cached(&dl_se->rb_node, &dl_rq->root);
	RB_CLEAR_NODE(&dl_se->rb_node);

	dec_dl_tasks(dl_se, dl_rq);
}
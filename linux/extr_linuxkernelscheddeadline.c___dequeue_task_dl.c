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
struct task_struct {int /*<<< orphan*/  dl; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue_dl_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dequeue_pushable_dl_task (struct rq*,struct task_struct*) ; 

__attribute__((used)) static void __dequeue_task_dl(struct rq *rq, struct task_struct *p, int flags)
{
	dequeue_dl_entity(&p->dl);
	dequeue_pushable_dl_task(rq, p);
}
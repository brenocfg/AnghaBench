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
struct tasklet_struct {struct tasklet_struct* next; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; int /*<<< orphan*/  count; } ;
struct tasklet_head {struct tasklet_struct** tail; struct tasklet_struct* head; } ;
struct softirq_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  TASKLET_STATE_SCHED ; 
 int /*<<< orphan*/  __raise_softirq_irqoff (unsigned int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ tasklet_trylock (struct tasklet_struct*) ; 
 int /*<<< orphan*/  tasklet_unlock (struct tasklet_struct*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tasklet_action_common(struct softirq_action *a,
				  struct tasklet_head *tl_head,
				  unsigned int softirq_nr)
{
	struct tasklet_struct *list;

	local_irq_disable();
	list = tl_head->head;
	tl_head->head = NULL;
	tl_head->tail = &tl_head->head;
	local_irq_enable();

	while (list) {
		struct tasklet_struct *t = list;

		list = list->next;

		if (tasklet_trylock(t)) {
			if (!atomic_read(&t->count)) {
				if (!test_and_clear_bit(TASKLET_STATE_SCHED,
							&t->state))
					BUG();
				t->func(t->data);
				tasklet_unlock(t);
				continue;
			}
			tasklet_unlock(t);
		}

		local_irq_disable();
		t->next = NULL;
		*tl_head->tail = t;
		tl_head->tail = &t->next;
		__raise_softirq_irqoff(softirq_nr);
		local_irq_enable();
	}
}
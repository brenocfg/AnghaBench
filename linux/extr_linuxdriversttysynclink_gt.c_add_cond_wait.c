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
struct cond_wait {struct cond_wait* next; int /*<<< orphan*/  wait; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_cond_wait(struct cond_wait **head, struct cond_wait *w)
{
	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&w->q, &w->wait);
	w->next = *head;
	*head = w;
}
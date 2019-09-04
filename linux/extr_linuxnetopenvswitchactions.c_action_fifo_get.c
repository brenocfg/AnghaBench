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
struct deferred_action {int dummy; } ;
struct action_fifo {int /*<<< orphan*/  tail; struct deferred_action* fifo; } ;

/* Variables and functions */
 scalar_t__ action_fifo_is_empty (struct action_fifo*) ; 

__attribute__((used)) static struct deferred_action *action_fifo_get(struct action_fifo *fifo)
{
	if (action_fifo_is_empty(fifo))
		return NULL;

	return &fifo->fifo[fifo->tail++];
}
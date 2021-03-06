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
struct nn_ctx {int /*<<< orphan*/  sync; int /*<<< orphan*/  events; int /*<<< orphan*/  eventsto; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_mutex_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_term (int /*<<< orphan*/ *) ; 

void nn_ctx_term (struct nn_ctx *self)
{
    nn_queue_term (&self->eventsto);
    nn_queue_term (&self->events);
    nn_mutex_term (&self->sync);
}
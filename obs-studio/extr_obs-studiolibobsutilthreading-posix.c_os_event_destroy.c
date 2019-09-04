#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ os_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void os_event_destroy(os_event_t *event)
{
	if (event) {
		pthread_mutex_destroy(&event->mutex);
		pthread_cond_destroy(&event->cond);
		bfree(event);
	}
}
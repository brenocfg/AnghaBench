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
typedef  int /*<<< orphan*/  os_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  OS_EVENT_TYPE_AUTO ; 
 int /*<<< orphan*/  clear_queue_signal ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ os_event_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_call_queue(void)
{
	os_event_t *event;
	if (os_event_init(&event, OS_EVENT_TYPE_AUTO) != 0)
		return;

	defer_call_post(clear_queue_signal, event);

	os_event_wait(event);
	os_event_destroy(event);
}
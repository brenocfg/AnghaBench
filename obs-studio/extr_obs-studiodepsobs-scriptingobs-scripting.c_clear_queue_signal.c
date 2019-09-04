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
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_queue_signal(void *p_event)
{
	os_event_t *event = p_event;
	os_event_signal(event);
}
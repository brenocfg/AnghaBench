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
typedef  enum os_event_type { ____Placeholder_os_event_type } os_event_type ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int OS_EVENT_TYPE_MANUAL ; 

int os_event_init(os_event_t **event, enum os_event_type type)
{
	HANDLE handle;

	handle = CreateEvent(NULL, (type == OS_EVENT_TYPE_MANUAL), FALSE, NULL);
	if (!handle)
		return -1;

	*event = (os_event_t *)handle;
	return 0;
}
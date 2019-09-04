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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int os_event_wait(os_event_t *event)
{
	DWORD code;

	if (!event)
		return EINVAL;

	code = WaitForSingleObject((HANDLE)event, INFINITE);
	if (code != WAIT_OBJECT_0)
		return EINVAL;

	return 0;
}
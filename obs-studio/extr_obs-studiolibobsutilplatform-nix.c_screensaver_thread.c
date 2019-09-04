#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stop_event; } ;
typedef  TYPE_1__ os_inhibit_t ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ os_event_timedwait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_screensaver (TYPE_1__*) ; 

__attribute__((used)) static void *screensaver_thread(void *param)
{
	os_inhibit_t *info = param;

	while (os_event_timedwait(info->stop_event, 30000) == ETIMEDOUT)
		reset_screensaver(info);

	return NULL;
}
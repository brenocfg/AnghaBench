#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* reason; int /*<<< orphan*/  attr; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  dbus; } ;
typedef  TYPE_1__ os_inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  dbus_sleep_info_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_inhibit_sleep_set_active (TYPE_1__*,int) ; 
 int /*<<< orphan*/  posix_spawnattr_destroy (int /*<<< orphan*/ *) ; 

void os_inhibit_sleep_destroy(os_inhibit_t *info)
{
	if (info) {
		os_inhibit_sleep_set_active(info, false);
#if HAVE_DBUS
		dbus_sleep_info_destroy(info->dbus);
#endif
		os_event_destroy(info->stop_event);
		posix_spawnattr_destroy(&info->attr);
		bfree(info->reason);
		bfree(info);
	}
}
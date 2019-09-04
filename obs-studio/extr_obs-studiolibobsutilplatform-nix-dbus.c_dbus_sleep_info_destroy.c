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
struct dbus_sleep_info {int /*<<< orphan*/  c; scalar_t__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct dbus_sleep_info*) ; 
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_pending_call_cancel (scalar_t__) ; 
 int /*<<< orphan*/  dbus_pending_call_unref (scalar_t__) ; 

void dbus_sleep_info_destroy(struct dbus_sleep_info *info)
{
	if (info) {
		if (info->pending) {
			dbus_pending_call_cancel(info->pending);
			dbus_pending_call_unref(info->pending);
		}

		dbus_connection_close(info->c);
		dbus_connection_unref(info->c);
		bfree(info);
	}
}
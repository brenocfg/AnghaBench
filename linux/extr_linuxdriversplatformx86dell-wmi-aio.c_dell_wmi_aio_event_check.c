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
typedef  int /*<<< orphan*/  u8 ;
struct dell_wmi_event {int type; int length; } ;

/* Variables and functions */

__attribute__((used)) static bool dell_wmi_aio_event_check(u8 *buffer, int length)
{
	struct dell_wmi_event *event = (struct dell_wmi_event *)buffer;

	if (event == NULL || length < 6)
		return false;

	if ((event->type == 0 || event->type == 0xf) &&
			event->length >= 2)
		return true;

	return false;
}
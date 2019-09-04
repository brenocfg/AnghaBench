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
struct charger_manager {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CM_EVENT_BATT_OUT ; 
 scalar_t__ cm_suspended ; 
 char** default_event_names ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_batt_present (struct charger_manager*) ; 
 int /*<<< orphan*/  uevent_notify (struct charger_manager*,char*) ; 

__attribute__((used)) static void battout_handler(struct charger_manager *cm)
{
	if (cm_suspended)
		device_set_wakeup_capable(cm->dev, true);

	if (!is_batt_present(cm)) {
		dev_emerg(cm->dev, "Battery Pulled Out!\n");
		uevent_notify(cm, default_event_names[CM_EVENT_BATT_OUT]);
	} else {
		uevent_notify(cm, "Battery Reinserted?");
	}
}
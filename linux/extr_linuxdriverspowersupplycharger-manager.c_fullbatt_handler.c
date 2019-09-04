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
struct charger_manager {scalar_t__ fullbatt_vchk_jiffies_at; int /*<<< orphan*/  dev; int /*<<< orphan*/  fullbatt_vchk_work; struct charger_desc* desc; } ;
struct charger_desc {int /*<<< orphan*/  fullbatt_vchkdrop_ms; int /*<<< orphan*/  fullbatt_vchkdrop_uV; } ;

/* Variables and functions */
 size_t CM_EVENT_BATT_FULL ; 
 scalar_t__ cm_suspended ; 
 int /*<<< orphan*/  cm_wq ; 
 int /*<<< orphan*/ * default_event_names ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uevent_notify (struct charger_manager*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fullbatt_handler(struct charger_manager *cm)
{
	struct charger_desc *desc = cm->desc;

	if (!desc->fullbatt_vchkdrop_uV || !desc->fullbatt_vchkdrop_ms)
		goto out;

	if (cm_suspended)
		device_set_wakeup_capable(cm->dev, true);

	mod_delayed_work(cm_wq, &cm->fullbatt_vchk_work,
			 msecs_to_jiffies(desc->fullbatt_vchkdrop_ms));
	cm->fullbatt_vchk_jiffies_at = jiffies + msecs_to_jiffies(
				       desc->fullbatt_vchkdrop_ms);

	if (cm->fullbatt_vchk_jiffies_at == 0)
		cm->fullbatt_vchk_jiffies_at = 1;

out:
	dev_info(cm->dev, "EVENT_HANDLE: Battery Fully Charged\n");
	uevent_notify(cm, default_event_names[CM_EVENT_BATT_FULL]);
}
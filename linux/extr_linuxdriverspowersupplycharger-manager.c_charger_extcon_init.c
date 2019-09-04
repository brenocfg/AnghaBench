#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct charger_manager {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct charger_cable {int /*<<< orphan*/  name; int /*<<< orphan*/  extcon_name; TYPE_1__ nb; int /*<<< orphan*/  extcon_dev; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charger_extcon_notifier ; 
 int /*<<< orphan*/  charger_extcon_work ; 
 int extcon_register_interest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int charger_extcon_init(struct charger_manager *cm,
		struct charger_cable *cable)
{
	int ret;

	/*
	 * Charger manager use Extcon framework to identify
	 * the charger cable among various external connector
	 * cable (e.g., TA, USB, MHL, Dock).
	 */
	INIT_WORK(&cable->wq, charger_extcon_work);
	cable->nb.notifier_call = charger_extcon_notifier;
	ret = extcon_register_interest(&cable->extcon_dev,
			cable->extcon_name, cable->name, &cable->nb);
	if (ret < 0) {
		pr_info("Cannot register extcon_dev for %s(cable: %s)\n",
			cable->extcon_name, cable->name);
	}

	return ret;
}
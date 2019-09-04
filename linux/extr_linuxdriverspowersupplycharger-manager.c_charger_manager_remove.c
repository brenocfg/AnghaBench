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
struct platform_device {int dummy; } ;
struct charger_regulator {int num_cables; int /*<<< orphan*/  consumer; struct charger_cable* cables; } ;
struct charger_manager {int /*<<< orphan*/  charger_psy; int /*<<< orphan*/  entry; struct charger_desc* desc; } ;
struct charger_desc {int num_charger_regulators; struct charger_regulator* charger_regulators; } ;
struct charger_cable {int /*<<< orphan*/  extcon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_list_mtx ; 
 int /*<<< orphan*/  cm_monitor_work ; 
 int /*<<< orphan*/  extcon_unregister_interest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct charger_manager* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_polling ; 
 int /*<<< orphan*/  try_charger_enable (struct charger_manager*,int) ; 

__attribute__((used)) static int charger_manager_remove(struct platform_device *pdev)
{
	struct charger_manager *cm = platform_get_drvdata(pdev);
	struct charger_desc *desc = cm->desc;
	int i = 0;
	int j = 0;

	/* Remove from the list */
	mutex_lock(&cm_list_mtx);
	list_del(&cm->entry);
	mutex_unlock(&cm_list_mtx);

	cancel_work_sync(&setup_polling);
	cancel_delayed_work_sync(&cm_monitor_work);

	for (i = 0 ; i < desc->num_charger_regulators ; i++) {
		struct charger_regulator *charger
				= &desc->charger_regulators[i];
		for (j = 0 ; j < charger->num_cables ; j++) {
			struct charger_cable *cable = &charger->cables[j];
			extcon_unregister_interest(&cable->extcon_dev);
		}
	}

	for (i = 0 ; i < desc->num_charger_regulators ; i++)
		regulator_put(desc->charger_regulators[i].consumer);

	power_supply_unregister(cm->charger_psy);

	try_charger_enable(cm, false);

	return 0;
}
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
struct bq24735 {int /*<<< orphan*/  charger; int /*<<< orphan*/  lock; scalar_t__ charging; } ;

/* Variables and functions */
 scalar_t__ bq24735_charger_is_present (struct bq24735*) ; 
 int /*<<< orphan*/  bq24735_disable_charging (struct bq24735*) ; 
 int /*<<< orphan*/  bq24735_enable_charging (struct bq24735*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bq24735_update(struct bq24735 *charger)
{
	mutex_lock(&charger->lock);

	if (charger->charging && bq24735_charger_is_present(charger))
		bq24735_enable_charging(charger);
	else
		bq24735_disable_charging(charger);

	mutex_unlock(&charger->lock);

	power_supply_changed(charger->charger);
}
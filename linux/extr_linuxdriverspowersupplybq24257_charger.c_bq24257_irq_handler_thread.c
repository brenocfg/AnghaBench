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
struct bq24257_state {int /*<<< orphan*/  power_good; int /*<<< orphan*/  fault; int /*<<< orphan*/  status; } ;
struct bq24257_device {int /*<<< orphan*/  charger; int /*<<< orphan*/  lock; struct bq24257_state state; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int bq24257_get_chip_state (struct bq24257_device*,struct bq24257_state*) ; 
 int /*<<< orphan*/  bq24257_handle_state_change (struct bq24257_device*,struct bq24257_state*) ; 
 int /*<<< orphan*/  bq24257_state_changed (struct bq24257_device*,struct bq24257_state*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bq24257_irq_handler_thread(int irq, void *private)
{
	int ret;
	struct bq24257_device *bq = private;
	struct bq24257_state state;

	ret = bq24257_get_chip_state(bq, &state);
	if (ret < 0)
		return IRQ_HANDLED;

	if (!bq24257_state_changed(bq, &state))
		return IRQ_HANDLED;

	dev_dbg(bq->dev, "irq(state changed): status/fault/pg = %d/%d/%d\n",
		state.status, state.fault, state.power_good);

	bq24257_handle_state_change(bq, &state);

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	power_supply_changed(bq->charger);

	return IRQ_HANDLED;
}
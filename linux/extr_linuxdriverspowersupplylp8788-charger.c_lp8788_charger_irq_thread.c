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
struct lp8788_charger_platform_data {scalar_t__ charger_event; } ;
struct lp8788_charger {int /*<<< orphan*/  charger_work; int /*<<< orphan*/  battery; int /*<<< orphan*/  charger; struct lp8788_charger_platform_data* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  LP8788_INT_BATT_LOW 132 
#define  LP8788_INT_CHG_INPUT_STATE 131 
#define  LP8788_INT_CHG_STATE 130 
#define  LP8788_INT_EOC 129 
#define  LP8788_INT_NO_BATT 128 
 int /*<<< orphan*/  lp8788_find_irq_id (struct lp8788_charger*,int,int*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lp8788_charger_irq_thread(int virq, void *ptr)
{
	struct lp8788_charger *pchg = ptr;
	struct lp8788_charger_platform_data *pdata = pchg->pdata;
	int id = -1;

	if (!lp8788_find_irq_id(pchg, virq, &id))
		return IRQ_NONE;

	switch (id) {
	case LP8788_INT_CHG_INPUT_STATE:
	case LP8788_INT_CHG_STATE:
	case LP8788_INT_EOC:
	case LP8788_INT_BATT_LOW:
	case LP8788_INT_NO_BATT:
		power_supply_changed(pchg->charger);
		power_supply_changed(pchg->battery);
		break;
	default:
		break;
	}

	/* report charger dectection event if used */
	if (!pdata)
		goto irq_handled;

	if (pdata->charger_event && id == LP8788_INT_CHG_INPUT_STATE)
		schedule_work(&pchg->charger_work);

irq_handled:
	return IRQ_HANDLED;
}
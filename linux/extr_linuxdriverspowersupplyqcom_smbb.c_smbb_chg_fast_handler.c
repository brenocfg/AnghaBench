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
struct smbb_charger {int /*<<< orphan*/  bat_psy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STATUS_CHG_FAST ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbb_set_line_flag (struct smbb_charger*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t smbb_chg_fast_handler(int irq, void *_data)
{
	struct smbb_charger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_FAST);
	power_supply_changed(chg->bat_psy);

	return IRQ_HANDLED;
}
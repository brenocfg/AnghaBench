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
struct power_supply {int dummy; } ;
struct bq24735 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bq24735_update (struct bq24735*) ; 
 struct bq24735* to_bq24735 (struct power_supply*) ; 

__attribute__((used)) static irqreturn_t bq24735_charger_isr(int irq, void *devid)
{
	struct power_supply *psy = devid;
	struct bq24735 *charger = to_bq24735(psy);

	bq24735_update(charger);

	return IRQ_HANDLED;
}
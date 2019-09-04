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
struct lp8727_psy {int /*<<< orphan*/  batt; int /*<<< orphan*/  usb; int /*<<< orphan*/  ac; } ;
struct lp8727_chg {struct lp8727_psy* psy; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp8727_unregister_psy(struct lp8727_chg *pchg)
{
	struct lp8727_psy *psy = pchg->psy;

	if (!psy)
		return;

	power_supply_unregister(psy->ac);
	power_supply_unregister(psy->usb);
	power_supply_unregister(psy->batt);
}
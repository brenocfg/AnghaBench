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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ST_CR ; 
 int AT91_ST_EXTEN ; 
 int AT91_ST_RSTEN ; 
 int /*<<< orphan*/  AT91_ST_WDMR ; 
 int AT91_ST_WDRST ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  regmap_st ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at91rm9200_restart(struct notifier_block *this,
					unsigned long mode, void *cmd)
{
	/*
	 * Perform a hardware reset with the use of the Watchdog timer.
	 */
	regmap_write(regmap_st, AT91_ST_WDMR,
		     AT91_ST_RSTEN | AT91_ST_EXTEN | 1);
	regmap_write(regmap_st, AT91_ST_CR, AT91_ST_WDRST);

	mdelay(2000);

	pr_emerg("Unable to restart system\n");
	return NOTIFY_DONE;
}
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
struct da9150_fg {int warn_soc; int crit_soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_QIF_CHARGE_LIMIT ; 
 int /*<<< orphan*/  DA9150_QIF_CHARGE_LIMIT_SIZE ; 
 int /*<<< orphan*/  DA9150_QIF_DISCHARGE_LIMIT ; 
 int /*<<< orphan*/  DA9150_QIF_DISCHARGE_LIMIT_SIZE ; 
 int /*<<< orphan*/  DA9150_QIF_SOC_PCT ; 
 int /*<<< orphan*/  DA9150_QIF_SOC_PCT_SIZE ; 
 int da9150_fg_read_attr_sync (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_write_attr_sync (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da9150_fg_soc_event_config(struct da9150_fg *fg)
{
	int soc;

	soc = da9150_fg_read_attr_sync(fg, DA9150_QIF_SOC_PCT,
				       DA9150_QIF_SOC_PCT_SIZE);

	if (soc > fg->warn_soc) {
		/* If SOC > warn level, set discharge warn level event */
		da9150_fg_write_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->warn_soc + 1);
	} else if ((soc <= fg->warn_soc) && (soc > fg->crit_soc)) {
		/*
		 * If SOC <= warn level, set discharge crit level event,
		 * and set charge warn level event.
		 */
		da9150_fg_write_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->crit_soc + 1);

		da9150_fg_write_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->warn_soc);
	} else if (soc <= fg->crit_soc) {
		/* If SOC <= crit level, set charge crit level event */
		da9150_fg_write_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->crit_soc);
	}
}
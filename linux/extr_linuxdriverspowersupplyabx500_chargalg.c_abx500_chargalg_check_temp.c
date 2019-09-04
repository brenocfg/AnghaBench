#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ temp; } ;
struct TYPE_4__ {int btemp_underover; int btemp_lowhigh; } ;
struct abx500_chargalg {scalar_t__ t_hyst_norm; scalar_t__ t_hyst_lowhigh; TYPE_3__ batt_data; int /*<<< orphan*/  dev; TYPE_2__* bm; TYPE_1__ events; } ;
struct TYPE_5__ {scalar_t__ temp_low; scalar_t__ temp_high; scalar_t__ temp_over; scalar_t__ temp_under; scalar_t__ temp_hysteresis; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void abx500_chargalg_check_temp(struct abx500_chargalg *di)
{
	if (di->batt_data.temp > (di->bm->temp_low + di->t_hyst_norm) &&
		di->batt_data.temp < (di->bm->temp_high - di->t_hyst_norm)) {
		/* Temp OK! */
		di->events.btemp_underover = false;
		di->events.btemp_lowhigh = false;
		di->t_hyst_norm = 0;
		di->t_hyst_lowhigh = 0;
	} else {
		if (((di->batt_data.temp >= di->bm->temp_high) &&
			(di->batt_data.temp <
				(di->bm->temp_over - di->t_hyst_lowhigh))) ||
			((di->batt_data.temp >
				(di->bm->temp_under + di->t_hyst_lowhigh)) &&
			(di->batt_data.temp <= di->bm->temp_low))) {
			/* TEMP minor!!!!! */
			di->events.btemp_underover = false;
			di->events.btemp_lowhigh = true;
			di->t_hyst_norm = di->bm->temp_hysteresis;
			di->t_hyst_lowhigh = 0;
		} else if (di->batt_data.temp <= di->bm->temp_under ||
			di->batt_data.temp >= di->bm->temp_over) {
			/* TEMP major!!!!! */
			di->events.btemp_underover = true;
			di->events.btemp_lowhigh = false;
			di->t_hyst_norm = 0;
			di->t_hyst_lowhigh = di->bm->temp_hysteresis;
		} else {
		/* Within hysteresis */
		dev_dbg(di->dev, "Within hysteresis limit temp: %d "
				"hyst_lowhigh %d, hyst normal %d\n",
				di->batt_data.temp, di->t_hyst_lowhigh,
				di->t_hyst_norm);
		}
	}
}
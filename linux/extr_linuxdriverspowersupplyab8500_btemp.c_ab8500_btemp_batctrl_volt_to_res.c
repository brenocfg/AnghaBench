#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ab8500_btemp {int curr_source; TYPE_1__* bm; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {scalar_t__ adc_therm; int gnd_lift_resistance; } ;

/* Variables and functions */
 scalar_t__ ABx500_ADC_THERM_BATCTRL ; 
 scalar_t__ is_ab8500_1p1_or_earlier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_btemp_batctrl_volt_to_res(struct ab8500_btemp *di,
	int v_batctrl, int inst_curr)
{
	int rbs;

	if (is_ab8500_1p1_or_earlier(di->parent)) {
		/*
		 * For ABB cut1.0 and 1.1 BAT_CTRL is internally
		 * connected to 1.8V through a 450k resistor
		 */
		return (450000 * (v_batctrl)) / (1800 - v_batctrl);
	}

	if (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL) {
		/*
		 * If the battery has internal NTC, we use the current
		 * source to calculate the resistance.
		 */
		rbs = (v_batctrl * 1000
		       - di->bm->gnd_lift_resistance * inst_curr)
		      / di->curr_source;
	} else {
		/*
		 * BAT_CTRL is internally
		 * connected to 1.8V through a 80k resistor
		 */
		rbs = (80000 * (v_batctrl)) / (1800 - v_batctrl);
	}

	return rbs;
}
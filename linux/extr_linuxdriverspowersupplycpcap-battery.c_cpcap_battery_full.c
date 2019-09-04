#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpcap_battery_state_data {int voltage; } ;
struct TYPE_3__ {int voltage_max_design; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
struct cpcap_battery_ddata {TYPE_2__ config; } ;

/* Variables and functions */
 struct cpcap_battery_state_data* cpcap_battery_latest (struct cpcap_battery_ddata*) ; 

__attribute__((used)) static bool cpcap_battery_full(struct cpcap_battery_ddata *ddata)
{
	struct cpcap_battery_state_data *state = cpcap_battery_latest(ddata);

	/* Basically anything that measures above 4347000 is full */
	if (state->voltage >= (ddata->config.info.voltage_max_design - 4000))
		return true;

	return false;
}
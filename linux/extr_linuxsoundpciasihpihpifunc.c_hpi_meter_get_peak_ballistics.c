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
typedef  scalar_t__ u32 ;
typedef  short u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_METER_PEAK_BALLISTICS ; 
 short hpi_control_param2_get (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

u16 hpi_meter_get_peak_ballistics(u32 h_control, u16 *pn_attack,
	u16 *pn_decay)
{
	u32 attack;
	u32 decay;
	u16 error;

	error = hpi_control_param2_get(h_control, HPI_METER_PEAK_BALLISTICS,
		&attack, &decay);

	if (pn_attack)
		*pn_attack = (short)attack;
	if (pn_decay)
		*pn_decay = (short)decay;

	return error;
}
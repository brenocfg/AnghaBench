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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int) ; 
 int UINT32_C (int) ; 
 scalar_t__ heatr_dur ; 
 scalar_t__ os_hum ; 
 scalar_t__ os_pres ; 
 scalar_t__ os_temp ; 

uint16_t calc_dur()
{
	uint32_t tph_dur; /* Calculate in us */

	/* TPH measurement duration */

	tph_dur = ((uint32_t) (os_temp + os_pres + os_hum) * UINT32_C(1963));
	tph_dur += UINT32_C(477 * 4); /* TPH switching duration */
	tph_dur += UINT32_C(477 * 5); /* Gas measurement duration */
	tph_dur += UINT32_C(500); /* Get it to the closest whole number.*/
	tph_dur /= UINT32_C(1000); /* Convert to ms */

	tph_dur += UINT32_C(1); /* Wake up duration of 1ms */
  NODE_DBG("tpc_dur: %d\n", tph_dur);
	/* The remaining time should be used for heating */
	return heatr_dur + (uint16_t) tph_dur;
}
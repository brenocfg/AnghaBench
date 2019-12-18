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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_TUNER_BAND ; 
 scalar_t__ hpi_control_param1_get (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

u16 hpi_tuner_get_band(u32 h_control, u16 *pw_band)
{
	u32 band = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_BAND, &band);
	if (pw_band)
		*pw_band = (u16)band;
	return error;
}
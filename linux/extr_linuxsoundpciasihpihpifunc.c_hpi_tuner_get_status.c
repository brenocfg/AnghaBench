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
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_TUNER_STATUS ; 
 scalar_t__ hpi_control_param1_get (int,int /*<<< orphan*/ ,int*) ; 

u16 hpi_tuner_get_status(u32 h_control, u16 *pw_status_mask, u16 *pw_status)
{
	u32 status = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_STATUS, &status);
	if (pw_status) {
		if (!error) {
			*pw_status_mask = (u16)(status >> 16);
			*pw_status = (u16)(status & 0xFFFF);
		} else {
			*pw_status_mask = 0;
			*pw_status = 0;
		}
	}
	return error;
}
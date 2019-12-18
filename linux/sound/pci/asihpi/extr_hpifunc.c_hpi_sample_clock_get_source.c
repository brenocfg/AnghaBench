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
 int /*<<< orphan*/  HPI_SAMPLECLOCK_SOURCE ; 
 scalar_t__ hpi_control_param1_get (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

u16 hpi_sample_clock_get_source(u32 h_control, u16 *pw_source)
{
	u16 err = 0;
	u32 source = 0;
	err = hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_SOURCE,
		&source);
	if (!err)
		if (pw_source)
			*pw_source = (u16)source;
	return err;
}
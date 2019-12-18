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
 int /*<<< orphan*/  HPI_EQUALIZER_NUM_FILTERS ; 
 scalar_t__ hpi_control_param2_get (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

u16 hpi_parametric_eq_get_info(u32 h_control, u16 *pw_number_of_bands,
	u16 *pw_on_off)
{
	u32 oB = 0;
	u32 oO = 0;
	u16 error = 0;

	error = hpi_control_param2_get(h_control, HPI_EQUALIZER_NUM_FILTERS,
		&oO, &oB);
	if (pw_number_of_bands)
		*pw_number_of_bands = (u16)oB;
	if (pw_on_off)
		*pw_on_off = (u16)oO;
	return error;
}
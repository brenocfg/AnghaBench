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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_EQUALIZER_NUM_FILTERS ; 
 int /*<<< orphan*/  hpi_control_param_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 hpi_parametric_eq_set_state(u32 h_control, u16 on_off)
{
	return hpi_control_param_set(h_control, HPI_EQUALIZER_NUM_FILTERS,
		on_off, 0);
}
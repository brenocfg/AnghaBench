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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_MICROPHONE_PHANTOM_POWER ; 
 scalar_t__ hpi_control_param_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 hpi_microphone_set_phantom_power(u32 h_control, u16 on_off)
{
	return hpi_control_param_set(h_control, HPI_MICROPHONE_PHANTOM_POWER,
		(u32)on_off, 0);
}
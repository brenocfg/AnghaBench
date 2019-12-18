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
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int BSP_MAX_DEVICES ; 
 int /*<<< orphan*/ * dsl_devices ; 

__attribute__((used)) static DSL_DEV_Device_t *
IFX_BSP_HandleGet (int maj, int num)
{
	if (num > BSP_MAX_DEVICES)
		return NULL;
	return &dsl_devices[num];
}
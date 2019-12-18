#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ base_address; } ;
typedef  TYPE_1__ DSL_DEV_Device_t ;

/* Variables and functions */
 scalar_t__ IFX_MEI_READ_REGISTER_L (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void
IFX_MEI_LongWordReadOffset (DSL_DEV_Device_t * pDev, u32 ul_address,
				  u32 * pul_data)
{
	*pul_data = IFX_MEI_READ_REGISTER_L (pDev->base_address + ul_address);
	rmb();
	return;
}
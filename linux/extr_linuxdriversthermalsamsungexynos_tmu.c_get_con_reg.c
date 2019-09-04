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
struct exynos_tmu_data {scalar_t__ soc; int reference_voltage; int gain; } ;

/* Variables and functions */
 int EXYNOS4412_MUX_ADDR_SHIFT ; 
 int EXYNOS4412_MUX_ADDR_VALUE ; 
 int EXYNOS_NOISE_CANCEL_MODE ; 
 int EXYNOS_TMU_BUF_SLOPE_SEL_MASK ; 
 int EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT ; 
 int EXYNOS_TMU_REF_VOLTAGE_MASK ; 
 int EXYNOS_TMU_REF_VOLTAGE_SHIFT ; 
 int EXYNOS_TMU_TRIP_MODE_MASK ; 
 int EXYNOS_TMU_TRIP_MODE_SHIFT ; 
 scalar_t__ SOC_ARCH_EXYNOS3250 ; 
 scalar_t__ SOC_ARCH_EXYNOS4412 ; 

__attribute__((used)) static u32 get_con_reg(struct exynos_tmu_data *data, u32 con)
{
	if (data->soc == SOC_ARCH_EXYNOS4412 ||
	    data->soc == SOC_ARCH_EXYNOS3250)
		con |= (EXYNOS4412_MUX_ADDR_VALUE << EXYNOS4412_MUX_ADDR_SHIFT);

	con &= ~(EXYNOS_TMU_REF_VOLTAGE_MASK << EXYNOS_TMU_REF_VOLTAGE_SHIFT);
	con |= data->reference_voltage << EXYNOS_TMU_REF_VOLTAGE_SHIFT;

	con &= ~(EXYNOS_TMU_BUF_SLOPE_SEL_MASK << EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT);
	con |= (data->gain << EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT);

	con &= ~(EXYNOS_TMU_TRIP_MODE_MASK << EXYNOS_TMU_TRIP_MODE_SHIFT);
	con |= (EXYNOS_NOISE_CANCEL_MODE << EXYNOS_TMU_TRIP_MODE_SHIFT);

	return con;
}
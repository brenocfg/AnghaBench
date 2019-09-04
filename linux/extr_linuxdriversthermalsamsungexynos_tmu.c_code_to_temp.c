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
typedef  int u16 ;
struct exynos_tmu_data {scalar_t__ cal_type; int temp_error1; int temp_error2; } ;

/* Variables and functions */
 int EXYNOS_FIRST_POINT_TRIM ; 
 int EXYNOS_SECOND_POINT_TRIM ; 
 scalar_t__ TYPE_ONE_POINT_TRIMMING ; 

__attribute__((used)) static int code_to_temp(struct exynos_tmu_data *data, u16 temp_code)
{
	if (data->cal_type == TYPE_ONE_POINT_TRIMMING)
		return temp_code - data->temp_error1 + EXYNOS_FIRST_POINT_TRIM;

	return (temp_code - data->temp_error1) *
		(EXYNOS_SECOND_POINT_TRIM - EXYNOS_FIRST_POINT_TRIM) /
		(data->temp_error2 - data->temp_error1) +
		EXYNOS_FIRST_POINT_TRIM;
}
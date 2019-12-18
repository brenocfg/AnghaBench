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
typedef  enum qsv_cpu_platform { ____Placeholder_qsv_cpu_platform } qsv_cpu_platform ;

/* Variables and functions */
 int QSV_CPU_PLATFORM_SKL ; 
 int qsv_get_cpu_platform () ; 

__attribute__((used)) static inline bool is_skl_or_greater_platform()
{
	enum qsv_cpu_platform plat = qsv_get_cpu_platform();
	return (plat >= QSV_CPU_PLATFORM_SKL);
}
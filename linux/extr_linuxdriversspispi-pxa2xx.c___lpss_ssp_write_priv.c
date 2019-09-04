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
struct driver_data {unsigned int lpss_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void __lpss_ssp_write_priv(struct driver_data *drv_data,
				  unsigned offset, u32 value)
{
	WARN_ON(!drv_data->lpss_base);
	writel(value, drv_data->lpss_base + offset);
}
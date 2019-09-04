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
 int /*<<< orphan*/  readl (unsigned int) ; 

__attribute__((used)) static u32 __lpss_ssp_read_priv(struct driver_data *drv_data, unsigned offset)
{
	WARN_ON(!drv_data->lpss_base);
	return readl(drv_data->lpss_base + offset);
}
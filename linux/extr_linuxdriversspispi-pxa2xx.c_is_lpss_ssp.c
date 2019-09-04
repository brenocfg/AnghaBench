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
struct driver_data {int ssp_type; } ;

/* Variables and functions */
#define  LPSS_BSW_SSP 133 
#define  LPSS_BXT_SSP 132 
#define  LPSS_BYT_SSP 131 
#define  LPSS_CNL_SSP 130 
#define  LPSS_LPT_SSP 129 
#define  LPSS_SPT_SSP 128 

__attribute__((used)) static bool is_lpss_ssp(const struct driver_data *drv_data)
{
	switch (drv_data->ssp_type) {
	case LPSS_LPT_SSP:
	case LPSS_BYT_SSP:
	case LPSS_BSW_SSP:
	case LPSS_SPT_SSP:
	case LPSS_BXT_SSP:
	case LPSS_CNL_SSP:
		return true;
	default:
		return false;
	}
}
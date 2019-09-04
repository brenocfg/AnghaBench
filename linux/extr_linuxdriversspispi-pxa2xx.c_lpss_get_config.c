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
struct lpss_config {int dummy; } ;
struct driver_data {size_t ssp_type; } ;

/* Variables and functions */
 size_t LPSS_LPT_SSP ; 
 struct lpss_config const* lpss_platforms ; 

__attribute__((used)) static inline const struct lpss_config
*lpss_get_config(const struct driver_data *drv_data)
{
	return &lpss_platforms[drv_data->ssp_type - LPSS_LPT_SSP];
}
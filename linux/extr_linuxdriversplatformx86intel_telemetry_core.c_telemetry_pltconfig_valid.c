#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ plt_config; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ telm_core_conf ; 

int telemetry_pltconfig_valid(void)
{
	if (telm_core_conf.plt_config)
		return 0;

	else
		return -EINVAL;
}
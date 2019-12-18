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
struct sst_hsw {int enabled_modules_rtd3; } ;

/* Variables and functions */

void sst_hsw_set_module_disabled_rtd3(struct sst_hsw *hsw, u32 module_id)
{
	hsw->enabled_modules_rtd3 &= ~(1 << module_id);
}
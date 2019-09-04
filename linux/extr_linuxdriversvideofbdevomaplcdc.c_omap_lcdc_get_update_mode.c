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
typedef  enum omapfb_update_mode { ____Placeholder_omapfb_update_mode } omapfb_update_mode ;
struct TYPE_2__ {int update_mode; } ;

/* Variables and functions */
 TYPE_1__ lcdc ; 

__attribute__((used)) static enum omapfb_update_mode omap_lcdc_get_update_mode(void)
{
	return lcdc.update_mode;
}
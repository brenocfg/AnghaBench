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
struct TYPE_2__ {int num_ovls; } ;

/* Variables and functions */
 TYPE_1__* omap_current_dss_features ; 

int dss_feat_get_num_ovls(void)
{
	return omap_current_dss_features->num_ovls;
}
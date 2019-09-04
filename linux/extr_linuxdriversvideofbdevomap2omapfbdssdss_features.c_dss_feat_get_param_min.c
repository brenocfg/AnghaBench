#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum dss_range_param { ____Placeholder_dss_range_param } dss_range_param ;
struct TYPE_4__ {TYPE_1__* dss_params; } ;
struct TYPE_3__ {unsigned long min; } ;

/* Variables and functions */
 TYPE_2__* omap_current_dss_features ; 

unsigned long dss_feat_get_param_min(enum dss_range_param param)
{
	return omap_current_dss_features->dss_params[param].min;
}
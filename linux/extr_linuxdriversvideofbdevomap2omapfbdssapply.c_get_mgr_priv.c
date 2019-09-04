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
struct omap_overlay_manager {size_t id; } ;
struct mgr_priv_data {int dummy; } ;
struct TYPE_2__ {struct mgr_priv_data* mgr_priv_data_array; } ;

/* Variables and functions */
 TYPE_1__ dss_data ; 

__attribute__((used)) static struct mgr_priv_data *get_mgr_priv(struct omap_overlay_manager *mgr)
{
	return &dss_data.mgr_priv_data_array[mgr->id];
}
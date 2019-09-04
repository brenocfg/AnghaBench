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
struct ovl_priv_data {int dummy; } ;
struct omap_overlay {size_t id; } ;
struct TYPE_2__ {struct ovl_priv_data* ovl_priv_data_array; } ;

/* Variables and functions */
 TYPE_1__ dss_data ; 

__attribute__((used)) static struct ovl_priv_data *get_ovl_priv(struct omap_overlay *ovl)
{
	return &dss_data.ovl_priv_data_array[ovl->id];
}
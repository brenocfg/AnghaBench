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
struct omap_overlay {int dummy; } ;

/* Variables and functions */
 int num_overlays ; 
 struct omap_overlay* overlays ; 

struct omap_overlay *omap_dss_get_overlay(int num)
{
	if (num >= num_overlays)
		return NULL;

	return &overlays[num];
}
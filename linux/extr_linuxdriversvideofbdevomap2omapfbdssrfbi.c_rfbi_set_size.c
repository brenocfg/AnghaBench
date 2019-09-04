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
typedef  void* u16 ;
struct omap_dss_device {int dummy; } ;
struct TYPE_3__ {void* y_res; void* x_res; } ;
struct TYPE_4__ {TYPE_1__ timings; } ;

/* Variables and functions */
 TYPE_2__ rfbi ; 

__attribute__((used)) static void rfbi_set_size(struct omap_dss_device *dssdev, u16 w, u16 h)
{
	rfbi.timings.x_res = w;
	rfbi.timings.y_res = h;
}
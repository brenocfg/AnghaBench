#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t channel; } ;
struct TYPE_5__ {TYPE_1__ rfbi; } ;
struct omap_dss_device {TYPE_2__ phy; } ;
struct TYPE_6__ {struct omap_dss_device** dssdev; } ;

/* Variables and functions */
 TYPE_3__ rfbi ; 

__attribute__((used)) static int rfbi_init_display(struct omap_dss_device *dssdev)
{
	rfbi.dssdev[dssdev->phy.rfbi.channel] = dssdev;
	return 0;
}
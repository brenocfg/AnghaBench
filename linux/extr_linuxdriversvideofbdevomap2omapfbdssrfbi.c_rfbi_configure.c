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
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {TYPE_1__ rfbi; } ;
struct omap_dss_device {TYPE_2__ phy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_lines; int /*<<< orphan*/  pixel_size; } ;

/* Variables and functions */
 TYPE_3__ rfbi ; 
 int rfbi_configure_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfbi_configure(struct omap_dss_device *dssdev)
{
	return rfbi_configure_bus(dssdev->phy.rfbi.channel, rfbi.pixel_size,
			rfbi.data_lines);
}
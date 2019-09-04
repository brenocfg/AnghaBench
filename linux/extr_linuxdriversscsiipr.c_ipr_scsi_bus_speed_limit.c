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
typedef  scalar_t__ u32 ;
struct ipr_ioa_cfg {TYPE_1__* bus_attr; } ;
struct TYPE_2__ {scalar_t__ max_xfer_rate; int /*<<< orphan*/  bus_width; } ;

/* Variables and functions */
 int IPR_MAX_NUM_BUSES ; 
 scalar_t__ ipr_get_max_scsi_speed (struct ipr_ioa_cfg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_scsi_bus_speed_limit(struct ipr_ioa_cfg *ioa_cfg)
{
	u32 max_xfer_rate;
	int i;

	for (i = 0; i < IPR_MAX_NUM_BUSES; i++) {
		max_xfer_rate = ipr_get_max_scsi_speed(ioa_cfg, i,
						       ioa_cfg->bus_attr[i].bus_width);

		if (max_xfer_rate < ioa_cfg->bus_attr[i].max_xfer_rate)
			ioa_cfg->bus_attr[i].max_xfer_rate = max_xfer_rate;
	}
}
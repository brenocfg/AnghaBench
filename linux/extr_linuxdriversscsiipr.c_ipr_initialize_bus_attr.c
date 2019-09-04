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
struct ipr_ioa_cfg {TYPE_1__* bus_attr; } ;
struct TYPE_2__ {int bus; int /*<<< orphan*/  max_xfer_rate; int /*<<< orphan*/  bus_width; scalar_t__ qas_enabled; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPR_DEFAULT_BUS_WIDTH ; 
 int IPR_MAX_NUM_BUSES ; 
 int /*<<< orphan*/  IPR_U160_SCSI_RATE ; 
 int /*<<< orphan*/ * ipr_max_bus_speeds ; 
 size_t ipr_max_speed ; 

__attribute__((used)) static void ipr_initialize_bus_attr(struct ipr_ioa_cfg *ioa_cfg)
{
	int i;

	for (i = 0; i < IPR_MAX_NUM_BUSES; i++) {
		ioa_cfg->bus_attr[i].bus = i;
		ioa_cfg->bus_attr[i].qas_enabled = 0;
		ioa_cfg->bus_attr[i].bus_width = IPR_DEFAULT_BUS_WIDTH;
		if (ipr_max_speed < ARRAY_SIZE(ipr_max_bus_speeds))
			ioa_cfg->bus_attr[i].max_xfer_rate = ipr_max_bus_speeds[ipr_max_speed];
		else
			ioa_cfg->bus_attr[i].max_xfer_rate = IPR_U160_SCSI_RATE;
	}
}
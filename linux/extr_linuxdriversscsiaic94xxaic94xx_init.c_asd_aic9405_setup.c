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
struct TYPE_2__ {int addr_range; int dev_name_base; int sata_name_base; scalar_t__ port_name_base; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;

/* Variables and functions */
 int asd_common_setup (struct asd_ha_struct*) ; 

__attribute__((used)) static int asd_aic9405_setup(struct asd_ha_struct *asd_ha)
{
	int err = asd_common_setup(asd_ha);

	if (err)
		return err;

	asd_ha->hw_prof.addr_range = 4;
	asd_ha->hw_prof.port_name_base = 0;
	asd_ha->hw_prof.dev_name_base = 4;
	asd_ha->hw_prof.sata_name_base = 8;

	return 0;
}
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
typedef  int u32 ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int,int) ; 

void pm80xx_pci_mem_copy(struct pm8001_hba_info  *pm8001_ha, u32 soffset,
				const void *destination,
				u32 dw_count, u32 bus_base_number)
{
	u32 index, value, offset;
	u32 *destination1;
	destination1 = (u32 *)destination;

	for (index = 0; index < dw_count; index += 4, destination1++) {
		offset = (soffset + index / 4);
		if (offset < (64 * 1024)) {
			value = pm8001_cr32(pm8001_ha, bus_base_number, offset);
			*destination1 =  cpu_to_le32(value);
		}
	}
	return;
}
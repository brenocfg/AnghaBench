#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ core_global_regs; } ;
typedef  TYPE_1__ dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 

void dwc_otg_dump_spram(dwc_otg_core_if_t * core_if)
{
	volatile uint8_t *addr, *start_addr, *end_addr;

	DWC_PRINTF("SPRAM Data:\n");
	start_addr = (void *)core_if->core_global_regs;
	DWC_PRINTF("Base Address: 0x%8lX\n", (unsigned long)start_addr);
	start_addr += 0x00028000;
	end_addr = (void *)core_if->core_global_regs;
	end_addr += 0x000280e0;

	for (addr = start_addr; addr < end_addr; addr += 16) {
		DWC_PRINTF
		    ("0x%8lX:\t%2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X\n",
		     (unsigned long)addr, addr[0], addr[1], addr[2], addr[3],
		     addr[4], addr[5], addr[6], addr[7], addr[8], addr[9],
		     addr[10], addr[11], addr[12], addr[13], addr[14], addr[15]
		    );
	}

	return;
}
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
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ C_DDR_STAT_REG ; 

__attribute__((used)) static void ddr_poll_until_not_busy(void)
{
	volatile UINT reg_tmp = 0;
	volatile UINT busy = 1;

	//Extra read to put in delay before starting to poll...
	reg_tmp = *(volatile UINT *) C_DDR_STAT_REG;      // read

	//POLL DDR_STAT register until no longer busy
	//!!! Ideally have a timeout on this.
	while (busy == 1) {
		reg_tmp = *(volatile UINT *) C_DDR_STAT_REG;      // read

		//when bit 31 is clear - core is no longer busy
		if ((reg_tmp & 0x80000000) == 0x00000000) {
			busy = 0;
		}
	}
}
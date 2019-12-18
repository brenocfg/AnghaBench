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

/* Variables and functions */
 int MAX_NOT_BUSY_LOOPS ; 
 int SATA_CMD_BUSY_BIT ; 
 int SATA_COMMAND_OFF ; 
 int /*<<< orphan*/  printf (char*) ; 
 int** sata_regs_base ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int wait_sata_command_not_busy(int device)
{
	/* Wait for data to be available */
	int status = 0;
	int loops = MAX_NOT_BUSY_LOOPS;
	do {
		if (!(*(sata_regs_base[device] + SATA_COMMAND_OFF)
			& (1 << SATA_CMD_BUSY_BIT))) {
			status = 1;
			break;
		}
		udelay(100);
	} while (--loops);

	if (!loops) {
		printf("wait_sata_command_not_busy() Timed out of wait for SATA command to finish\n");
	}

	return status;
}
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
struct icm {scalar_t__ vnd_cap; int /*<<< orphan*/  upstream_port; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ PCIE2CIO_CMD ; 
 int PCIE2CIO_CMD_START ; 
 int PCIE2CIO_CMD_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int pci2cio_wait_completion(struct icm *icm, unsigned long timeout_msec)
{
	unsigned long end = jiffies + msecs_to_jiffies(timeout_msec);
	u32 cmd;

	do {
		pci_read_config_dword(icm->upstream_port,
				      icm->vnd_cap + PCIE2CIO_CMD, &cmd);
		if (!(cmd & PCIE2CIO_CMD_START)) {
			if (cmd & PCIE2CIO_CMD_TIMEOUT)
				break;
			return 0;
		}

		msleep(50);
	} while (time_before(jiffies, end));

	return -ETIMEDOUT;
}
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
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 int ATA_SECTORWORDS ; 
 int /*<<< orphan*/  device_select (int) ; 
 int /*<<< orphan*/ * disk_present ; 
 int /*<<< orphan*/  dma_start_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sata_bug_6320_workaround (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_dma_not_busy (int) ; 
 int /*<<< orphan*/  wait_no_error (int) ; 
 scalar_t__ wait_not_busy (int,int) ; 

void ide_input_data(int device, ulong *sect_buf, int words)
{
	/* Only permit accesses to disks found to be present during ide_preinit() */
	if (!disk_present[device]) {
		return;
	}

	/* Select the required internal SATA drive */
	device_select(device);

	/* Start the DMA channel receiving data from the SATA core into the passed buffer */
	dma_start_read(sect_buf, words << 2);

	/* Sata core should finish before DMA */
	if (wait_not_busy(device, 30)) {
		printf("Timed out of wait for SATA device %d to have BUSY clear\n",
			device);
	}
	if (!wait_no_error(device)) {
		printf("oxnas_sata_output_data() Wait for ATA no-error timed-out\n");
	}

	/* Wait for DMA to finish */
	if (!wait_dma_not_busy(device)) {
		printf("Timed out of wait for DMA channel for SATA device %d to have in-progress clear\n",
			device);
	}

	if (words == ATA_SECTORWORDS)
		sata_bug_6320_workaround(device, sect_buf + words - 2);
}
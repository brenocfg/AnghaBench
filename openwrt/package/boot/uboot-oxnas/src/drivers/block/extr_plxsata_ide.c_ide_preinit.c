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
 int /*<<< orphan*/  ATA_PORT_NSECT ; 
 int CONFIG_SYS_IDE_MAXDEVICE ; 
 int SATA_CONTROL_OFF ; 
 int SATA_DRIVE_CONTROL_OFF ; 
 scalar_t__ SATA_HOST_REGS_BASE ; 
 int SATA_INT_CLR_OFF ; 
 int SATA_INT_ENABLE_CLR_OFF ; 
 int /*<<< orphan*/  SATA_SCR_ERROR ; 
 int /*<<< orphan*/  SATA_SCR_STATUS ; 
 unsigned long SATA_SCTL_CLR_ERR ; 
 int /*<<< orphan*/  SYS_CTRL_CLK_DMA ; 
 int /*<<< orphan*/  SYS_CTRL_CLK_SATA ; 
 int /*<<< orphan*/  SYS_CTRL_RST_SATA ; 
 int /*<<< orphan*/  SYS_CTRL_RST_SATA_LINK ; 
 int /*<<< orphan*/  SYS_CTRL_RST_SATA_PHY ; 
 int /*<<< orphan*/  SYS_CTRL_RST_SGDMA ; 
 int* disk_present ; 
 int /*<<< orphan*/  enable_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_outb (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_reset (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  reset_block (int /*<<< orphan*/ ,int) ; 
 unsigned long** sata_regs_base ; 
 int scr_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_FIS (int) ; 
 scalar_t__ wait_not_busy (int,int) ; 
 int /*<<< orphan*/  workaround5458 () ; 

int ide_preinit(void)
{
	int num_disks_found = 0;

	/* Initialise records of which disks are present to all present */
	int i;
	for (i = 0; i < CONFIG_SYS_IDE_MAXDEVICE; i++) {
		disk_present[i] = 1;
	}

	/* Block reset SATA and DMA cores */
	reset_block(SYS_CTRL_RST_SATA, 1);
	reset_block(SYS_CTRL_RST_SATA_LINK, 1);
	reset_block(SYS_CTRL_RST_SATA_PHY, 1);
	reset_block(SYS_CTRL_RST_SGDMA, 1);

	/* Enable clocks to SATA and DMA cores */
	enable_clock(SYS_CTRL_CLK_SATA);
	enable_clock(SYS_CTRL_CLK_DMA);

	udelay(5000);
	reset_block(SYS_CTRL_RST_SATA_PHY, 0);
	udelay(50);
	reset_block(SYS_CTRL_RST_SATA, 0);
	reset_block(SYS_CTRL_RST_SATA_LINK, 0);
	udelay(50);
	reset_block(SYS_CTRL_RST_SGDMA, 0);
	udelay(100);
	/* Apply the Synopsis SATA PHY workarounds */
	workaround5458();
	udelay(10000);

	/* disable and clear core interrupts */
	*((unsigned long*) SATA_HOST_REGS_BASE + SATA_INT_ENABLE_CLR_OFF) =
		~0UL;
	*((unsigned long*) SATA_HOST_REGS_BASE + SATA_INT_CLR_OFF) = ~0UL;

	int device;
	for (device = 0; device < CONFIG_SYS_IDE_MAXDEVICE; device++) {
		int found = 0;
		int retries = 1;

		/* Disable SATA interrupts */
		*(sata_regs_base[device] + SATA_INT_ENABLE_CLR_OFF) = ~0UL;

		/* Clear any pending SATA interrupts */
		*(sata_regs_base[device] + SATA_INT_CLR_OFF) = ~0UL;

		do {
			/* clear sector count register for FIS detection */
			ide_outb(device, ATA_PORT_NSECT, 0);

			/* Get the PHY working */
			if (!phy_reset(device)) {
				printf("SATA PHY not ready for device %d\n",
					device);
				break;
			}

			if (!wait_FIS(device)) {
				printf("No FIS received from device %d\n",
					device);
			} else {
				if ((scr_read(device, SATA_SCR_STATUS) & 0xf)
					== 0x3) {
					if (wait_not_busy(device, 30)) {
						printf("Timed out of wait for SATA device %d to have BUSY clear\n",
							device);
					} else {
						++num_disks_found;
						found = 1;
					}
				} else {
					printf("No SATA device %d found, PHY status = 0x%08x\n",
						device,
						scr_read(
							device,
							SATA_SCR_STATUS));
				}
				break;
			}
		} while (retries--);

		/* Record whether disk is present, so won't attempt to access it later */
		disk_present[device] = found;
	}

	/* post disk detection clean-up */
	for (device = 0; device < CONFIG_SYS_IDE_MAXDEVICE; device++) {
		if (disk_present[device]) {
			/* set as ata-5 (28-bit) */
			*(sata_regs_base[device] + SATA_DRIVE_CONTROL_OFF) =
				0UL;

			/* clear phy/link errors */
			scr_write(device, SATA_SCR_ERROR, ~0);

			/* clear host errors */
			*(sata_regs_base[device] + SATA_CONTROL_OFF) |=
				SATA_SCTL_CLR_ERR;

			/* clear interrupt register as this clears the error bit in the IDE
			 status register */
			*(sata_regs_base[device] + SATA_INT_CLR_OFF) = ~0UL;
		}
	}

	return !num_disks_found;
}
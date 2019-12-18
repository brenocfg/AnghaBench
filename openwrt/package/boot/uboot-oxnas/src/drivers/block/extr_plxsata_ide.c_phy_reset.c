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
 int LOS_AND_TX_LVL ; 
 int PHY_LOOP_COUNT ; 
 int SATA_SCR_CONTROL ; 
 int SATA_SCR_ERROR ; 
 int /*<<< orphan*/  SATA_SCR_STATUS ; 
 int SATA_STD_ASYNC_REGS_OFF ; 
 int TX_ATTEN ; 
 int scr_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_write (int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int phy_reset(int device)
{
	int phy_status = 0;
	int loops = 0;

	scr_write(device, (0x60 - SATA_STD_ASYNC_REGS_OFF) / 4, LOS_AND_TX_LVL);
	scr_write(device, (0x70 - SATA_STD_ASYNC_REGS_OFF) / 4, TX_ATTEN);

	/* limit it to Gen-1 SATA (1.5G) */
	scr_write(device, SATA_SCR_CONTROL, 0x311); /* Issue phy wake & core reset */
	scr_read(device, SATA_SCR_STATUS); /* Dummy read; flush */
	udelay(1000);
	scr_write(device, SATA_SCR_CONTROL, 0x310); /* Issue phy wake & clear core reset */

	/* Wait for upto 5 seconds for PHY to become ready */
	do {
		udelay(200000);
		if ((scr_read(device, SATA_SCR_STATUS) & 0xf) == 3) {
			scr_write(device, SATA_SCR_ERROR, ~0);
			phy_status = 1;
			break;
		}
		//printf("No SATA PHY found status:0x%x\n", scr_read(device, SATA_SCR_STATUS));
	} while (++loops < PHY_LOOP_COUNT);

	if (phy_status) {
		udelay(500000); /* wait half a second */
	}

	return phy_status;
}
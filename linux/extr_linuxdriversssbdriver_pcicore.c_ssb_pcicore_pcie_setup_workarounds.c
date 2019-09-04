#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ssb_pcicore {TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_PCICORE_SPROM (int) ; 
 int pcicore_read16 (struct ssb_pcicore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write16 (struct ssb_pcicore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_pcicore_serdes_workaround (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_pcie_mdio_write (struct ssb_pcicore*,int const,int,int) ; 
 int ssb_pcie_read (struct ssb_pcicore*,int) ; 
 int /*<<< orphan*/  ssb_pcie_write (struct ssb_pcicore*,int,int) ; 

__attribute__((used)) static void ssb_pcicore_pcie_setup_workarounds(struct ssb_pcicore *pc)
{
	u32 tmp;
	u8 rev = pc->dev->id.revision;

	if (rev == 0 || rev == 1) {
		/* TLP Workaround register. */
		tmp = ssb_pcie_read(pc, 0x4);
		tmp |= 0x8;
		ssb_pcie_write(pc, 0x4, tmp);
	}
	if (rev == 1) {
		/* DLLP Link Control register. */
		tmp = ssb_pcie_read(pc, 0x100);
		tmp |= 0x40;
		ssb_pcie_write(pc, 0x100, tmp);
	}

	if (rev == 0) {
		const u8 serdes_rx_device = 0x1F;

		ssb_pcie_mdio_write(pc, serdes_rx_device,
					2 /* Timer */, 0x8128);
		ssb_pcie_mdio_write(pc, serdes_rx_device,
					6 /* CDR */, 0x0100);
		ssb_pcie_mdio_write(pc, serdes_rx_device,
					7 /* CDR BW */, 0x1466);
	} else if (rev == 3 || rev == 4 || rev == 5) {
		/* TODO: DLLP Power Management Threshold */
		ssb_pcicore_serdes_workaround(pc);
		/* TODO: ASPM */
	} else if (rev == 7) {
		/* TODO: No PLL down */
	}

	if (rev >= 6) {
		/* Miscellaneous Configuration Fixup */
		tmp = pcicore_read16(pc, SSB_PCICORE_SPROM(5));
		if (!(tmp & 0x8000))
			pcicore_write16(pc, SSB_PCICORE_SPROM(5),
					tmp | 0x8000);
	}
}
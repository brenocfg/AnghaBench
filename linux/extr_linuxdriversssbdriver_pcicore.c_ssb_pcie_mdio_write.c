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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ssb_pcicore {TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int pcicore_read32 (struct ssb_pcicore*,int const) ; 
 int /*<<< orphan*/  pcicore_write32 (struct ssb_pcicore*,int const,int) ; 
 int /*<<< orphan*/  ssb_pcie_mdio_set_phy (struct ssb_pcicore*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ssb_pcie_mdio_write(struct ssb_pcicore *pc, u8 device,
				u8 address, u16 data)
{
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
	int max_retries = 10;
	u32 v;
	int i;

	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_write32(pc, mdio_control, v);

	if (pc->dev->id.revision >= 10) {
		max_retries = 200;
		ssb_pcie_mdio_set_phy(pc, device);
	}

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 28); /* Write Transaction */
	v |= (1 << 17); /* Turnaround */
	if (pc->dev->id.revision < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	v |= data;
	pcicore_write32(pc, mdio_data, v);
	/* Wait for the device to complete the transaction */
	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, mdio_control);
		if (v & 0x100 /* Trans complete */)
			break;
		msleep(1);
	}
	pcicore_write32(pc, mdio_control, 0);
}
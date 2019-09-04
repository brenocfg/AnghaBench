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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FIRMWARE_IMAGE_BASE ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  HOST_CMD_CSR ; 
 int /*<<< orphan*/  M2H_CMD_DONE_CSR ; 
 int /*<<< orphan*/  MAC_CSR0 ; 
 int /*<<< orphan*/  MAC_CSR1 ; 
 int /*<<< orphan*/  MAC_CSR1_BBP_RESET ; 
 int /*<<< orphan*/  MAC_CSR1_HOST_READY ; 
 int /*<<< orphan*/  MAC_CSR1_SOFT_RESET ; 
 int /*<<< orphan*/  MCU_CNTL_CSR ; 
 int /*<<< orphan*/  MCU_CNTL_CSR_READY ; 
 int /*<<< orphan*/  MCU_CNTL_CSR_RESET ; 
 int /*<<< orphan*/  MCU_CNTL_CSR_SELECT_BANK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 scalar_t__ rt2x00_get_field32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t const) ; 
 int rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt61pci_load_firmware(struct rt2x00_dev *rt2x00dev,
				 const u8 *data, const size_t len)
{
	int i;
	u32 reg;

	/*
	 * Wait for stable hardware.
	 */
	for (i = 0; i < 100; i++) {
		reg = rt2x00mmio_register_read(rt2x00dev, MAC_CSR0);
		if (reg)
			break;
		msleep(1);
	}

	if (!reg) {
		rt2x00_err(rt2x00dev, "Unstable hardware\n");
		return -EBUSY;
	}

	/*
	 * Prepare MCU and mailbox for firmware loading.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 1);
	rt2x00mmio_register_write(rt2x00dev, MCU_CNTL_CSR, reg);
	rt2x00mmio_register_write(rt2x00dev, M2H_CMD_DONE_CSR, 0xffffffff);
	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);
	rt2x00mmio_register_write(rt2x00dev, HOST_CMD_CSR, 0);

	/*
	 * Write firmware to device.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 1);
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_SELECT_BANK, 1);
	rt2x00mmio_register_write(rt2x00dev, MCU_CNTL_CSR, reg);

	rt2x00mmio_register_multiwrite(rt2x00dev, FIRMWARE_IMAGE_BASE,
				       data, len);

	rt2x00_set_field32(&reg, MCU_CNTL_CSR_SELECT_BANK, 0);
	rt2x00mmio_register_write(rt2x00dev, MCU_CNTL_CSR, reg);

	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 0);
	rt2x00mmio_register_write(rt2x00dev, MCU_CNTL_CSR, reg);

	for (i = 0; i < 100; i++) {
		reg = rt2x00mmio_register_read(rt2x00dev, MCU_CNTL_CSR);
		if (rt2x00_get_field32(reg, MCU_CNTL_CSR_READY))
			break;
		msleep(1);
	}

	if (i == 100) {
		rt2x00_err(rt2x00dev, "MCU Control register not ready\n");
		return -EBUSY;
	}

	/*
	 * Hardware needs another millisecond before it is ready.
	 */
	msleep(1);

	/*
	 * Reset MAC and BBP registers.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00mmio_register_write(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00mmio_register_write(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_HOST_READY, 1);
	rt2x00mmio_register_write(rt2x00dev, MAC_CSR1, reg);

	return 0;
}
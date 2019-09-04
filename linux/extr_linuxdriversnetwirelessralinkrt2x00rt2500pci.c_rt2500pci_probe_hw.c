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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  rssi_offset; int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_RSSI_OFFSET ; 
 int /*<<< orphan*/  GPIOCSR ; 
 int /*<<< orphan*/  GPIOCSR_DIR0 ; 
 int /*<<< orphan*/  REQUIRE_ATIM_QUEUE ; 
 int /*<<< orphan*/  REQUIRE_DMA ; 
 int /*<<< orphan*/  REQUIRE_SW_SEQNO ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2500pci_init_eeprom (struct rt2x00_dev*) ; 
 int rt2500pci_probe_hw_mode (struct rt2x00_dev*) ; 
 int rt2500pci_validate_eeprom (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500pci_probe_hw(struct rt2x00_dev *rt2x00dev)
{
	int retval;
	u32 reg;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2500pci_validate_eeprom(rt2x00dev);
	if (retval)
		return retval;

	retval = rt2500pci_init_eeprom(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Enable rfkill polling by setting GPIO direction of the
	 * rfkill switch GPIO pin correctly.
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, GPIOCSR);
	rt2x00_set_field32(&reg, GPIOCSR_DIR0, 1);
	rt2x00mmio_register_write(rt2x00dev, GPIOCSR, reg);

	/*
	 * Initialize hw specifications.
	 */
	retval = rt2500pci_probe_hw_mode(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * This device requires the atim queue and DMA-mapped skbs.
	 */
	__set_bit(REQUIRE_ATIM_QUEUE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_SW_SEQNO, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	return 0;
}
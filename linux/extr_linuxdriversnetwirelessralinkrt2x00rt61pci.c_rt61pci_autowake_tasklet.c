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
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  M2H_CMD_DONE_CSR ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_TWAKEUP ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt61pci_enable_mcu_interrupt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt61pci_wakeup (struct rt2x00_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt61pci_autowake_tasklet(unsigned long data)
{
	struct rt2x00_dev *rt2x00dev = (struct rt2x00_dev *)data;
	rt61pci_wakeup(rt2x00dev);
	rt2x00mmio_register_write(rt2x00dev,
				  M2H_CMD_DONE_CSR, 0xffffffff);
	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt61pci_enable_mcu_interrupt(rt2x00dev, MCU_INT_MASK_CSR_TWAKEUP);
}
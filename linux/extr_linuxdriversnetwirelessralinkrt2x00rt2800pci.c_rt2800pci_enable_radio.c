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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2M_MAILBOX_CID ; 
 int /*<<< orphan*/  H2M_MAILBOX_STATUS ; 
 int /*<<< orphan*/  MCU_SLEEP ; 
 int /*<<< orphan*/  MCU_WAKEUP ; 
 int /*<<< orphan*/  TOKEN_RADIO_OFF ; 
 int /*<<< orphan*/  TOKEN_WAKEUP ; 
 int /*<<< orphan*/  rt2800_mcu_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int rt2800mmio_enable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800pci_mcu_status (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800pci_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	int retval;

	retval = rt2800mmio_enable_radio(rt2x00dev);
	if (retval)
		return retval;

	/* After resume MCU_BOOT_SIGNAL will trash these. */
	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_STATUS, ~0);
	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_CID, ~0);

	rt2800_mcu_request(rt2x00dev, MCU_SLEEP, TOKEN_RADIO_OFF, 0xff, 0x02);
	rt2800pci_mcu_status(rt2x00dev, TOKEN_RADIO_OFF);

	rt2800_mcu_request(rt2x00dev, MCU_WAKEUP, TOKEN_WAKEUP, 0, 0);
	rt2800pci_mcu_status(rt2x00dev, TOKEN_WAKEUP);

	return retval;
}
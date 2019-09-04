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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2M_MAILBOX_CID ; 
 int /*<<< orphan*/  H2M_MAILBOX_CID_CMD0 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CID_CMD1 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CID_CMD2 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CID_CMD3 ; 
 int /*<<< orphan*/  H2M_MAILBOX_STATUS ; 
 int /*<<< orphan*/  REGISTER_BUSY_DELAY ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 scalar_t__ const rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_is_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800pci_mcu_status(struct rt2x00_dev *rt2x00dev, const u8 token)
{
	unsigned int i;
	u32 reg;

	/*
	 * SOC devices don't support MCU requests.
	 */
	if (rt2x00_is_soc(rt2x00dev))
		return;

	for (i = 0; i < 200; i++) {
		reg = rt2x00mmio_register_read(rt2x00dev, H2M_MAILBOX_CID);

		if ((rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD0) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD1) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD2) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD3) == token))
			break;

		udelay(REGISTER_BUSY_DELAY);
	}

	if (i == 200)
		rt2x00_err(rt2x00dev, "MCU request failed, no response from hardware\n");

	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_STATUS, ~0);
	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_CID, ~0);
}
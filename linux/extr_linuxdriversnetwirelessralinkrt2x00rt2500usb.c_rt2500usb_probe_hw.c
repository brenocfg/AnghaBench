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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int /*<<< orphan*/  rssi_offset; int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_HW_CRYPTO ; 
 int /*<<< orphan*/  DEFAULT_RSSI_OFFSET ; 
 int /*<<< orphan*/  MAC_CSR19 ; 
 int /*<<< orphan*/  MAC_CSR19_DIR0 ; 
 int /*<<< orphan*/  REQUIRE_ATIM_QUEUE ; 
 int /*<<< orphan*/  REQUIRE_BEACON_GUARD ; 
 int /*<<< orphan*/  REQUIRE_COPY_IV ; 
 int /*<<< orphan*/  REQUIRE_PS_AUTOWAKE ; 
 int /*<<< orphan*/  REQUIRE_SW_SEQNO ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_nohwcrypt ; 
 int rt2500usb_init_eeprom (struct rt2x00_dev*) ; 
 int rt2500usb_probe_hw_mode (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2500usb_validate_eeprom (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_probe_hw(struct rt2x00_dev *rt2x00dev)
{
	int retval;
	u16 reg;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2500usb_validate_eeprom(rt2x00dev);
	if (retval)
		return retval;

	retval = rt2500usb_init_eeprom(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Enable rfkill polling by setting GPIO direction of the
	 * rfkill switch GPIO pin correctly.
	 */
	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR19);
	rt2x00_set_field16(&reg, MAC_CSR19_DIR0, 0);
	rt2500usb_register_write(rt2x00dev, MAC_CSR19, reg);

	/*
	 * Initialize hw specifications.
	 */
	retval = rt2500usb_probe_hw_mode(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * This device requires the atim queue
	 */
	__set_bit(REQUIRE_ATIM_QUEUE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_BEACON_GUARD, &rt2x00dev->cap_flags);
	if (!modparam_nohwcrypt) {
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
		__set_bit(REQUIRE_COPY_IV, &rt2x00dev->cap_flags);
	}
	__set_bit(REQUIRE_SW_SEQNO, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	return 0;
}
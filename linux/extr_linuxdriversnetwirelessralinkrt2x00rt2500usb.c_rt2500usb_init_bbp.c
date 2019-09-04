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
typedef  int u8 ;
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  EEPROM_BBP_REG_ID ; 
 unsigned int EEPROM_BBP_SIZE ; 
 scalar_t__ EEPROM_BBP_START ; 
 int /*<<< orphan*/  EEPROM_BBP_VALUE ; 
 int /*<<< orphan*/  rt2500usb_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2500usb_wait_bbp_ready (struct rt2x00_dev*) ; 
 int rt2x00_eeprom_read (struct rt2x00_dev*,scalar_t__) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_init_bbp(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u16 eeprom;
	u8 value;
	u8 reg_id;

	if (unlikely(rt2500usb_wait_bbp_ready(rt2x00dev)))
		return -EACCES;

	rt2500usb_bbp_write(rt2x00dev, 3, 0x02);
	rt2500usb_bbp_write(rt2x00dev, 4, 0x19);
	rt2500usb_bbp_write(rt2x00dev, 14, 0x1c);
	rt2500usb_bbp_write(rt2x00dev, 15, 0x30);
	rt2500usb_bbp_write(rt2x00dev, 16, 0xac);
	rt2500usb_bbp_write(rt2x00dev, 18, 0x18);
	rt2500usb_bbp_write(rt2x00dev, 19, 0xff);
	rt2500usb_bbp_write(rt2x00dev, 20, 0x1e);
	rt2500usb_bbp_write(rt2x00dev, 21, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 22, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 23, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 24, 0x80);
	rt2500usb_bbp_write(rt2x00dev, 25, 0x50);
	rt2500usb_bbp_write(rt2x00dev, 26, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 27, 0x23);
	rt2500usb_bbp_write(rt2x00dev, 30, 0x10);
	rt2500usb_bbp_write(rt2x00dev, 31, 0x2b);
	rt2500usb_bbp_write(rt2x00dev, 32, 0xb9);
	rt2500usb_bbp_write(rt2x00dev, 34, 0x12);
	rt2500usb_bbp_write(rt2x00dev, 35, 0x50);
	rt2500usb_bbp_write(rt2x00dev, 39, 0xc4);
	rt2500usb_bbp_write(rt2x00dev, 40, 0x02);
	rt2500usb_bbp_write(rt2x00dev, 41, 0x60);
	rt2500usb_bbp_write(rt2x00dev, 53, 0x10);
	rt2500usb_bbp_write(rt2x00dev, 54, 0x18);
	rt2500usb_bbp_write(rt2x00dev, 56, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 57, 0x10);
	rt2500usb_bbp_write(rt2x00dev, 58, 0x08);
	rt2500usb_bbp_write(rt2x00dev, 61, 0x60);
	rt2500usb_bbp_write(rt2x00dev, 62, 0x10);
	rt2500usb_bbp_write(rt2x00dev, 75, 0xff);

	for (i = 0; i < EEPROM_BBP_SIZE; i++) {
		eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBP_START + i);

		if (eeprom != 0xffff && eeprom != 0x0000) {
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2500usb_bbp_write(rt2x00dev, reg_id, value);
		}
	}

	return 0;
}
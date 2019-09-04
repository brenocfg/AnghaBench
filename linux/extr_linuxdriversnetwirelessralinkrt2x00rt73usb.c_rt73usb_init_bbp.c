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
 int rt2x00_eeprom_read (struct rt2x00_dev*,scalar_t__) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt73usb_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt73usb_wait_bbp_ready (struct rt2x00_dev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt73usb_init_bbp(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	if (unlikely(rt73usb_wait_bbp_ready(rt2x00dev)))
		return -EACCES;

	rt73usb_bbp_write(rt2x00dev, 3, 0x80);
	rt73usb_bbp_write(rt2x00dev, 15, 0x30);
	rt73usb_bbp_write(rt2x00dev, 21, 0xc8);
	rt73usb_bbp_write(rt2x00dev, 22, 0x38);
	rt73usb_bbp_write(rt2x00dev, 23, 0x06);
	rt73usb_bbp_write(rt2x00dev, 24, 0xfe);
	rt73usb_bbp_write(rt2x00dev, 25, 0x0a);
	rt73usb_bbp_write(rt2x00dev, 26, 0x0d);
	rt73usb_bbp_write(rt2x00dev, 32, 0x0b);
	rt73usb_bbp_write(rt2x00dev, 34, 0x12);
	rt73usb_bbp_write(rt2x00dev, 37, 0x07);
	rt73usb_bbp_write(rt2x00dev, 39, 0xf8);
	rt73usb_bbp_write(rt2x00dev, 41, 0x60);
	rt73usb_bbp_write(rt2x00dev, 53, 0x10);
	rt73usb_bbp_write(rt2x00dev, 54, 0x18);
	rt73usb_bbp_write(rt2x00dev, 60, 0x10);
	rt73usb_bbp_write(rt2x00dev, 61, 0x04);
	rt73usb_bbp_write(rt2x00dev, 62, 0x04);
	rt73usb_bbp_write(rt2x00dev, 75, 0xfe);
	rt73usb_bbp_write(rt2x00dev, 86, 0xfe);
	rt73usb_bbp_write(rt2x00dev, 88, 0xfe);
	rt73usb_bbp_write(rt2x00dev, 90, 0x0f);
	rt73usb_bbp_write(rt2x00dev, 99, 0x00);
	rt73usb_bbp_write(rt2x00dev, 102, 0x16);
	rt73usb_bbp_write(rt2x00dev, 107, 0x04);

	for (i = 0; i < EEPROM_BBP_SIZE; i++) {
		eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBP_START + i);

		if (eeprom != 0xffff && eeprom != 0x0000) {
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt73usb_bbp_write(rt2x00dev, reg_id, value);
		}
	}

	return 0;
}
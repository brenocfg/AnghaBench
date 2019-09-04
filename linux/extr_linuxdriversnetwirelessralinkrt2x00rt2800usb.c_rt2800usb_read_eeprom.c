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
struct rt2x00_dev {int /*<<< orphan*/  eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_SIZE ; 
 int rt2800_read_eeprom_efuse (struct rt2x00_dev*) ; 
 int rt2800usb_efuse_detect (struct rt2x00_dev*) ; 
 int rt2x00usb_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800usb_read_eeprom(struct rt2x00_dev *rt2x00dev)
{
	int retval;

	retval = rt2800usb_efuse_detect(rt2x00dev);
	if (retval < 0)
		return retval;
	if (retval)
		retval = rt2800_read_eeprom_efuse(rt2x00dev);
	else
		retval = rt2x00usb_eeprom_read(rt2x00dev, rt2x00dev->eeprom,
					       EEPROM_SIZE);

	return retval;
}
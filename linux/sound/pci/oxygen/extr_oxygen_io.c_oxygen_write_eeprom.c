#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct oxygen {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OXYGEN_EEPROM_BUSY ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_DATA ; 
 unsigned int OXYGEN_EEPROM_DIR_WRITE ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 

void oxygen_write_eeprom(struct oxygen *chip, unsigned int index, u16 value)
{
	unsigned int timeout;

	oxygen_write16(chip, OXYGEN_EEPROM_DATA, value);
	oxygen_write8(chip, OXYGEN_EEPROM_CONTROL,
		      index | OXYGEN_EEPROM_DIR_WRITE);
	for (timeout = 0; timeout < 10; ++timeout) {
		msleep(1);
		if (!(oxygen_read8(chip, OXYGEN_EEPROM_STATUS)
		      & OXYGEN_EEPROM_BUSY))
			return;
	}
	dev_err(chip->card->dev, "EEPROM write timeout\n");
}
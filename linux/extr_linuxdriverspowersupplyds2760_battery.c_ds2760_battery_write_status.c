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
struct ds2760_device_info {char* raw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2760_EEPROM_BLOCK1 ; 
 size_t DS2760_STATUS_REG ; 
 int /*<<< orphan*/  DS2760_STATUS_WRITE_REG ; 
 int /*<<< orphan*/  w1_ds2760_recall_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_store_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ds2760_battery_write_status(struct ds2760_device_info *di,
					char status)
{
	if (status == di->raw[DS2760_STATUS_REG])
		return;

	w1_ds2760_write(di->dev, &status, DS2760_STATUS_WRITE_REG, 1);
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
}
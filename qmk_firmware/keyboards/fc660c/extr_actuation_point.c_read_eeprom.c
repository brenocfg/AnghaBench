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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD5258_ADDR ; 
 int /*<<< orphan*/  AD5258_INST_EEPROM ; 
 int /*<<< orphan*/  I2C_NACK ; 
 int /*<<< orphan*/  i2c_master_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_stop () ; 
 int /*<<< orphan*/  i2c_master_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_start_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_start_write (int /*<<< orphan*/ ) ; 

uint8_t read_eeprom(void) {
    i2c_start_write(AD5258_ADDR);
    i2c_master_write(AD5258_INST_EEPROM);
    i2c_start_read(AD5258_ADDR);
    uint8_t ret = i2c_master_read(I2C_NACK);
    i2c_master_stop();
    return ret;
}
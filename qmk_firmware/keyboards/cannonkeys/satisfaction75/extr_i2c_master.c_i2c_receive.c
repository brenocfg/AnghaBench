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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  i2c_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DRIVER ; 
 int /*<<< orphan*/  MS2ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chibios_to_qmk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2cMasterReceiveTimeout (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2cStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2c_address ; 
 int /*<<< orphan*/  i2cconfig ; 

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  msg_t status = i2cMasterReceiveTimeout(&I2C_DRIVER, (i2c_address >> 1), data, length, MS2ST(timeout));
  return chibios_to_qmk(status);
}
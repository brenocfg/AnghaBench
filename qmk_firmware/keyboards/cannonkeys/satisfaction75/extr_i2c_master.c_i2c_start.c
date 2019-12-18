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
typedef  int /*<<< orphan*/  i2c_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DRIVER ; 
 int /*<<< orphan*/  I2C_STATUS_SUCCESS ; 
 int /*<<< orphan*/  i2cStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_address ; 
 int /*<<< orphan*/  i2cconfig ; 

i2c_status_t i2c_start(uint8_t address)
{
  i2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return I2C_STATUS_SUCCESS;
}
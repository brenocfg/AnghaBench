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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOTDOX_I2C_TIMEOUT ; 
 int /*<<< orphan*/  I2C_ADDR_READ ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int /*<<< orphan*/  i2c_initialized ; 
 scalar_t__ i2c_read_nack (int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (scalar_t__,int /*<<< orphan*/ ) ; 

uint8_t left_read(uint8_t reg, uint8_t *data)
{
  if (!i2c_initialized)
  {
    return 0;
  }

  uint8_t ret = 0;

  ret = i2c_start(I2C_ADDR_WRITE, HOTDOX_I2C_TIMEOUT);     if (ret) goto out;
  ret = i2c_write(reg, HOTDOX_I2C_TIMEOUT);                if (ret) goto out;
  ret = i2c_start(I2C_ADDR_READ, HOTDOX_I2C_TIMEOUT);      if (ret) goto out;

  *data = i2c_read_nack(HOTDOX_I2C_TIMEOUT);

out:
  i2c_stop();
  return ret;
}
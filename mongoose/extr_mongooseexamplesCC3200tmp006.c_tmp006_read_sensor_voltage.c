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
 int I2C_IF_ReadFrom (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int) ; 
 unsigned char TMP006_REG_SENSOR_VOLTAGE ; 

double tmp006_read_sensor_voltage(uint8_t addr) {
  unsigned char reg = TMP006_REG_SENSOR_VOLTAGE;
  unsigned char val[2] = {0, 0};
  int status = I2C_IF_ReadFrom(addr, &reg, 1, val, 2);
  if (status < 0) return -1000;
  int voltage = (val[0] << 8) | val[1];
  if (val[0] & 0x80) voltage = -((1 << 16) - voltage);
  return voltage * 0.00015625;
}
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
 unsigned char TMP006_REG_DIE_TEMP ; 

double tmp006_read_die_temp(uint8_t addr) {
  unsigned char reg = TMP006_REG_DIE_TEMP;
  unsigned char val[2] = {0, 0};
  int status = I2C_IF_ReadFrom(addr, &reg, 1, val, 2);
  if (status < 0) return -1000;
  int temp = (val[0] << 6) | (val[1] >> 2);
  if (val[0] & 0x80) temp = -((1 << 14) - temp);
  return temp / 32.0;
}
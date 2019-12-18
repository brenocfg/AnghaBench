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
typedef  int i2c_status_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR (int) ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int TWI_CMD_KEYSCAN_INTERVAL ; 
 int i2c_transmit (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_set_keyscan_interval(int hand, int delay) {
  uint8_t buf[] = {TWI_CMD_KEYSCAN_INTERVAL, delay};
  i2c_status_t ret = i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  return ret;
}
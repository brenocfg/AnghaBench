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

/* Variables and functions */
 unsigned char I2C_WRITE ; 
 unsigned char i2c_master_start (unsigned char) ; 

__attribute__((used)) static inline unsigned char i2c_start_write(unsigned char addr) {
  return i2c_master_start((addr << 1) | I2C_WRITE);
}
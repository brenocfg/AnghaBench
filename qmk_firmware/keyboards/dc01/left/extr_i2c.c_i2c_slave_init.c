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

/* Variables and functions */
 int TWAR ; 
 int TWCR ; 
 int TWEA ; 
 int TWEN ; 
 int TWIE ; 
 int TWINT ; 

void i2c_slave_init(uint8_t address) {
  TWAR = address << 0; // slave i2c address
  // TWEN  - twi enable
  // TWEA  - enable address acknowledgement
  // TWINT - twi interrupt flag
  // TWIE  - enable the twi interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}
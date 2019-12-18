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
 int /*<<< orphan*/  TWAR ; 
 int TWCR ; 
 int TWEA ; 
 int TWEN ; 
 int TWIE ; 
 int TWINT ; 

void i2c_slave_init(uint8_t address) {
    // load address into TWI address register
    TWAR = address;
    // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
    TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
}
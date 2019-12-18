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
 int TWCR ; 
 int TWEA ; 
 int TWEN ; 

void i2c_slave_stop(void) {
    // clear acknowledge and enable bits
    TWCR &= ~((1 << TWEA) | (1 << TWEN));
}
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
 int F_CPU ; 
 int SCL_CLOCK ; 
 int TWBR ; 
 scalar_t__ TWSR ; 

void i2c_master_init(void) {
  // no prescaler
  TWSR = 0;
  // Set TWI clock frequency to SCL_CLOCK. Need TWBR>10.
  // Check datasheets for more info.
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}
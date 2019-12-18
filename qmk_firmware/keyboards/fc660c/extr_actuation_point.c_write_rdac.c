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
 int /*<<< orphan*/  AD5258_ADDR ; 
 int AD5258_INST_RDAC ; 
 int /*<<< orphan*/  i2c_master_stop () ; 
 int /*<<< orphan*/  i2c_master_write (int) ; 
 int /*<<< orphan*/  i2c_start_write (int /*<<< orphan*/ ) ; 

void write_rdac(uint8_t rdac) {
    // write RDAC register:
    i2c_start_write(AD5258_ADDR);
    i2c_master_write(AD5258_INST_RDAC);
    i2c_master_write(rdac & 0x3F);
    i2c_master_stop();
}
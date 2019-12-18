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
 int /*<<< orphan*/  i2c_master_init () ; 
 int read_eeprom () ; 
 int /*<<< orphan*/  write_rdac (int) ; 

void adjust_actuation_point(int offset) {
    i2c_master_init();
    uint8_t rdac = read_eeprom() + offset;
    if (rdac > 63) { // protects from under and overflows
        if (offset > 0)
            write_rdac(63);
        else
            write_rdac(0);
    } else {
        write_rdac(rdac);
    }
}
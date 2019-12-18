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
 int /*<<< orphan*/  i2c_init () ; 

void pca9555_init(uint8_t slave_addr) {
    static uint8_t s_init = 0;
    if (!s_init) {
        i2c_init();

        s_init = 1;
    }

    // TODO: could check device connected
    // i2c_start(SLAVE_TO_ADDR(slave) | I2C_WRITE);
    // i2c_stop();
}
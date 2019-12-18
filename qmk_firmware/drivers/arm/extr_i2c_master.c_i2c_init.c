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
 int /*<<< orphan*/  I2C1_SCL ; 
 int /*<<< orphan*/  I2C1_SCL_BANK ; 
 int /*<<< orphan*/  I2C1_SCL_PAL_MODE ; 
 int /*<<< orphan*/  I2C1_SDA ; 
 int /*<<< orphan*/  I2C1_SDA_BANK ; 
 int /*<<< orphan*/  I2C1_SDA_PAL_MODE ; 
 int PAL_MODE_ALTERNATE (int /*<<< orphan*/ ) ; 
 int PAL_MODE_INPUT ; 
 int PAL_MODE_STM32_ALTERNATE_OPENDRAIN ; 
 int PAL_STM32_OTYPE_OPENDRAIN ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((weak)) void i2c_init(void) {
    // Try releasing special pins for a short time
    palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
    palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);

    chThdSleepMilliseconds(10);
#ifdef USE_I2CV1
    palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
    palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif
}
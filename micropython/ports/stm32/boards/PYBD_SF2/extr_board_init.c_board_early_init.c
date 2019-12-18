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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDEV_IOCTL_INIT ; 
 int /*<<< orphan*/  MP_HAL_PIN_MODE_OUTPUT ; 
 int /*<<< orphan*/  MP_HAL_PIN_PULL_NONE ; 
 int /*<<< orphan*/  mp_hal_pin_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_pin_EN_3V3 ; 
 int /*<<< orphan*/  spi_bdev2 ; 
 int /*<<< orphan*/  spi_bdev_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spiflash2_config ; 

void board_early_init(void) {
    // Configure EN_3V3 as an output pin, but keep it turned off
    mp_hal_pin_config(pyb_pin_EN_3V3, MP_HAL_PIN_MODE_OUTPUT, MP_HAL_PIN_PULL_NONE, 0);

    // Explicitly init SPI2 because it's not enabled as a block device
    spi_bdev_ioctl(&spi_bdev2, BDEV_IOCTL_INIT, (uint32_t)&spiflash2_config);
}
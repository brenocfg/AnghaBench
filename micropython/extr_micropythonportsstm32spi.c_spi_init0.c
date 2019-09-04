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

void spi_init0(void) {
    // Initialise the SPI handles.
    // The structs live on the BSS so all other fields will be zero after a reset.
    #if defined(MICROPY_HW_SPI1_SCK)
    SPIHandle1.Instance = SPI1;
    #endif
    #if defined(MICROPY_HW_SPI2_SCK)
    SPIHandle2.Instance = SPI2;
    #endif
    #if defined(MICROPY_HW_SPI3_SCK)
    SPIHandle3.Instance = SPI3;
    #endif
    #if defined(MICROPY_HW_SPI4_SCK)
    SPIHandle4.Instance = SPI4;
    #endif
    #if defined(MICROPY_HW_SPI5_SCK)
    SPIHandle5.Instance = SPI5;
    #endif
    #if defined(MICROPY_HW_SPI6_SCK)
    SPIHandle6.Instance = SPI6;
    #endif
}
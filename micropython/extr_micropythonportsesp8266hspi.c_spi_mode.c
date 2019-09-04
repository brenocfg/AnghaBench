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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSPI ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CK_I_EDGE ; 
 int /*<<< orphan*/  SPI_CK_OUT_EDGE ; 
 int /*<<< orphan*/  SPI_IDLE_EDGE ; 
 int /*<<< orphan*/  SPI_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_USER (int /*<<< orphan*/ ) ; 

void spi_mode(uint8_t spi_no, uint8_t spi_cpha, uint8_t spi_cpol) {
    if (spi_cpol) {
        SET_PERI_REG_MASK(SPI_PIN(HSPI), SPI_IDLE_EDGE);
    } else {
        CLEAR_PERI_REG_MASK(SPI_PIN(HSPI), SPI_IDLE_EDGE);
    }
    if (spi_cpha == spi_cpol) {
        // Mode 3 - MOSI is set on falling edge of clock
        // Mode 0 - MOSI is set on falling edge of clock
        CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_CK_OUT_EDGE);
        SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_CK_I_EDGE);
    } else {
        // Mode 2 - MOSI is set on rising edge of clock
        // Mode 1 - MOSI is set on rising edge of clock
        SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_CK_OUT_EDGE);
        CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_CK_I_EDGE);
    }
}
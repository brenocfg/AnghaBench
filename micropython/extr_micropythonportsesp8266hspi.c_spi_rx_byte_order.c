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
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_RD_BYTE_ORDER ; 
 int /*<<< orphan*/  SPI_USER (scalar_t__) ; 

void spi_rx_byte_order(uint8_t spi_no, uint8_t byte_order) {
    if (byte_order) {
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_RD_BYTE_ORDER);
    } else {
        CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_RD_BYTE_ORDER);
    }
}
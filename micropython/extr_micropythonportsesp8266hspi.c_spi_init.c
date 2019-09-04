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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_BYTE_ORDER_HIGH_TO_LOW ; 
 int /*<<< orphan*/  SPI_CLK_CNTDIV ; 
 int /*<<< orphan*/  SPI_CLK_PREDIV ; 
 int /*<<< orphan*/  SPI_CLK_USE_DIV ; 
 int SPI_CS_HOLD ; 
 int SPI_CS_SETUP ; 
 int /*<<< orphan*/  SPI_FLASH_MODE ; 
 int /*<<< orphan*/  SPI_USER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_init_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_rx_byte_order (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_tx_byte_order (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_init(uint8_t spi_no) {
    spi_init_gpio(spi_no, SPI_CLK_USE_DIV);
    spi_clock(spi_no, SPI_CLK_PREDIV, SPI_CLK_CNTDIV);
    spi_tx_byte_order(spi_no, SPI_BYTE_ORDER_HIGH_TO_LOW);
    spi_rx_byte_order(spi_no, SPI_BYTE_ORDER_HIGH_TO_LOW);

    SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_CS_SETUP|SPI_CS_HOLD);
    CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_FLASH_MODE);
}
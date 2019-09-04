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
typedef  int uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int SPI_ORDER_LSB ; 
 int SPI_ORDER_MSB ; 
 int SPI_RD_BYTE_ORDER ; 
 int /*<<< orphan*/  SPI_USER (int) ; 
 int SPI_WR_BYTE_ORDER ; 

void spi_mast_byte_order(uint8 spi_no, uint8 order)
{
    if(spi_no > 1)
        return;

    if (order == SPI_ORDER_MSB) {
	SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_RD_BYTE_ORDER | SPI_WR_BYTE_ORDER);
    } else if (order == SPI_ORDER_LSB) {
	CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_RD_BYTE_ORDER | SPI_WR_BYTE_ORDER);
    }
}
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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIPHS_IO_MUX ; 
 int SPI_CLKCNT_H ; 
 int SPI_CLKCNT_H_S ; 
 int SPI_CLKCNT_L ; 
 int SPI_CLKCNT_L_S ; 
 int SPI_CLKCNT_N ; 
 int SPI_CLKCNT_N_S ; 
 int SPI_CLKDIV_PRE ; 
 int SPI_CLKDIV_PRE_S ; 
 int SPI_CLK_EQU_SYSCLK ; 
 int /*<<< orphan*/  SPI_CLOCK (int) ; 
 int SPI_HSPI ; 
 int SPI_SPI ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int* spi_clkdiv ; 

uint32_t spi_set_clkdiv(uint8 spi_no, uint32_t clock_div)
{
	uint32_t tmp_clkdiv;

	if (spi_no > 1) return 0; //handle invalid input number
	tmp_clkdiv = spi_clkdiv[spi_no];

	if (clock_div > 1) {
		uint8 i, k;
		i = (clock_div / 40) ? (clock_div / 40) : 1;
		k = clock_div / i;
		WRITE_PERI_REG(SPI_CLOCK(spi_no),
			       (((i - 1) & SPI_CLKDIV_PRE) << SPI_CLKDIV_PRE_S) |
			       (((k - 1) & SPI_CLKCNT_N) << SPI_CLKCNT_N_S) |
			       ((((k + 1) / 2 - 1) & SPI_CLKCNT_H) << SPI_CLKCNT_H_S) |
			       (((k - 1) & SPI_CLKCNT_L) << SPI_CLKCNT_L_S)); //clear bit 31,set SPI clock div
	} else {
		WRITE_PERI_REG(SPI_CLOCK(spi_no), SPI_CLK_EQU_SYSCLK); // 80Mhz speed
	}

	if(spi_no==SPI_SPI){
		WRITE_PERI_REG(PERIPHS_IO_MUX, 0x005 | (clock_div <= 1 ? 0x100 : 0));
	}
	else if(spi_no==SPI_HSPI){
		WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105 | (clock_div <= 1 ? 0x200 : 0));
	}

	spi_clkdiv[spi_no] = clock_div;

	return tmp_clkdiv;
}
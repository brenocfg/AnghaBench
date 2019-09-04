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
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_MTCK_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_MTDI_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_MTDO_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_MTMS_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SD_CLK_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SD_CMD_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SD_DATA0_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SD_DATA1_U ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int SPI_CLKCNT_H ; 
 int SPI_CLKCNT_H_S ; 
 int SPI_CLKCNT_L ; 
 int SPI_CLKCNT_L_S ; 
 int SPI_CLKCNT_N ; 
 int SPI_CLKCNT_N_S ; 
 int SPI_CLKDIV_PRE ; 
 int SPI_CLKDIV_PRE_S ; 
 int /*<<< orphan*/  SPI_CLOCK (int) ; 
 int SPI_CS_HOLD ; 
 int SPI_CS_SETUP ; 
 int /*<<< orphan*/  SPI_FLASH_MODE ; 
 int SPI_HSPI ; 
 int SPI_SPI ; 
 int /*<<< orphan*/  SPI_USER (int) ; 
 int SPI_USR_COMMAND ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 

void spi_lcd_mode_init(uint8 spi_no)
{
	uint32 regvalue;
	if(spi_no>1) 		return; //handle invalid input number
	//bit9 of PERIPHS_IO_MUX should be cleared when HSPI clock doesn't equal CPU clock
	//bit8 of PERIPHS_IO_MUX should be cleared when SPI clock doesn't equal CPU clock
	if(spi_no==SPI_SPI){
		WRITE_PERI_REG(PERIPHS_IO_MUX, 0x005); //clear bit9,and bit8
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_CLK_U, 1);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_CMD_U, 1);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA0_U, 1);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA1_U, 1);//configure io to spi mode
	}else if(spi_no==SPI_HSPI){
		WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105); //clear bit9
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, 2);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);//configure io to spi mode
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);//configure io to spi mode
	}

	SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_CS_SETUP|SPI_CS_HOLD|SPI_USR_COMMAND);
	CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_FLASH_MODE);
	// SPI clock=CPU clock/8
	WRITE_PERI_REG(SPI_CLOCK(spi_no),
					((1&SPI_CLKDIV_PRE)<<SPI_CLKDIV_PRE_S)|
					((3&SPI_CLKCNT_N)<<SPI_CLKCNT_N_S)|
					((1&SPI_CLKCNT_H)<<SPI_CLKCNT_H_S)|
					((3&SPI_CLKCNT_L)<<SPI_CLKCNT_L_S)); //clear bit 31,set SPI clock div

}
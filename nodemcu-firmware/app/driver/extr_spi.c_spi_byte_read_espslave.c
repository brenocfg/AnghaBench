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
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_CMD (int) ; 
 int /*<<< orphan*/  SPI_USER (int) ; 
 int /*<<< orphan*/  SPI_USER2 (int) ; 
 int SPI_USR ; 
 int SPI_USR_ADDR ; 
 int SPI_USR_COMMAND_BITLEN ; 
 int SPI_USR_COMMAND_BITLEN_S ; 
 int SPI_USR_DUMMY ; 
 int SPI_USR_MISO ; 
 int SPI_USR_MOSI ; 
 int /*<<< orphan*/  SPI_W0 (int) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 

void spi_byte_read_espslave(uint8 spi_no,uint8 *data)
 {
	uint32 regvalue;

	if(spi_no>1) 		return; //handle invalid input number

	while(READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR);

	SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_MISO);
	CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_MOSI|SPI_USR_ADDR|SPI_USR_DUMMY);
		//SPI_FLASH_USER2 bit28-31 is cmd length,cmd bit length is value(0-15)+1,
	// bit15-0 is cmd value.
	//0x70000000 is for 8bits cmd, 0x06 is eps8266 slave read cmd value
	WRITE_PERI_REG(SPI_USER2(spi_no),
					((7&SPI_USR_COMMAND_BITLEN)<<SPI_USR_COMMAND_BITLEN_S)|6);
	SET_PERI_REG_MASK(SPI_CMD(spi_no), SPI_USR);

	while(READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR);
	*data=(uint8)(READ_PERI_REG(SPI_W0(spi_no))&0xff);
 }
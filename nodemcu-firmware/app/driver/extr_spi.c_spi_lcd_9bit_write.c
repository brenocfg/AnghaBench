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
typedef  int uint32 ;

/* Variables and functions */
 int BIT15 ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_CMD (int) ; 
 int /*<<< orphan*/  SPI_USER2 (int) ; 
 int SPI_USR ; 
 int SPI_USR_COMMAND_BITLEN ; 
 int SPI_USR_COMMAND_BITLEN_S ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 

void spi_lcd_9bit_write(uint8 spi_no,uint8 high_bit,uint8 low_8bit)
{
	uint32 regvalue;
	uint8 bytetemp;
	if(spi_no>1) 		return; //handle invalid input number

	if(high_bit)		bytetemp=(low_8bit>>1)|0x80;
	else				bytetemp=(low_8bit>>1)&0x7f;

	regvalue= ((8&SPI_USR_COMMAND_BITLEN)<<SPI_USR_COMMAND_BITLEN_S)|((uint32)bytetemp);		//configure transmission variable,9bit transmission length and first 8 command bit
	if(low_8bit&0x01) 	regvalue|=BIT15;        //write the 9th bit
	while(READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR);		//waiting for spi module available
	WRITE_PERI_REG(SPI_USER2(spi_no), regvalue);				//write  command and command length into spi reg
	SET_PERI_REG_MASK(SPI_CMD(spi_no), SPI_USR);		//transmission start
}
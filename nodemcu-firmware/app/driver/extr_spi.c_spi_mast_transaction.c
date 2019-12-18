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
typedef  int uint16 ;
typedef  int sint16 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_ADDR (int) ; 
 int /*<<< orphan*/  SPI_CMD (int) ; 
 int SPI_DOUTDIN ; 
 int /*<<< orphan*/  SPI_USER (int) ; 
 int /*<<< orphan*/  SPI_USER1 (int) ; 
 int /*<<< orphan*/  SPI_USER2 (int) ; 
 int SPI_USR ; 
 int SPI_USR_ADDR ; 
 int SPI_USR_ADDR_BITLEN ; 
 int SPI_USR_ADDR_BITLEN_S ; 
 int SPI_USR_COMMAND ; 
 int SPI_USR_COMMAND_BITLEN ; 
 int SPI_USR_COMMAND_BITLEN_S ; 
 int SPI_USR_COMMAND_VALUE ; 
 int SPI_USR_DUMMY ; 
 int SPI_USR_DUMMY_CYCLELEN ; 
 int SPI_USR_DUMMY_CYCLELEN_S ; 
 int SPI_USR_MISO ; 
 int SPI_USR_MISO_BITLEN ; 
 int SPI_USR_MISO_BITLEN_S ; 
 int SPI_USR_MOSI ; 
 int SPI_USR_MOSI_BITLEN ; 
 int SPI_USR_MOSI_BITLEN_S ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 

void spi_mast_transaction(uint8 spi_no, uint8 cmd_bitlen, uint16 cmd_data, uint8 addr_bitlen, uint32 addr_data,
                          uint16 mosi_bitlen, uint8 dummy_bitlen, sint16 miso_bitlen)
{
    if (spi_no > 1)
        return; // handle invalid input number

    while(READ_PERI_REG(SPI_CMD(spi_no)) & SPI_USR);

    // default disable COMMAND, ADDR, MOSI, DUMMY, MISO, and DOUTDIN (aka full-duplex)
    CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_COMMAND|SPI_USR_ADDR|SPI_USR_MOSI|SPI_USR_DUMMY|SPI_USR_MISO|SPI_DOUTDIN);
    // default set bit lengths
    WRITE_PERI_REG(SPI_USER1(spi_no),
                   ((addr_bitlen - 1)  & SPI_USR_ADDR_BITLEN)    << SPI_USR_ADDR_BITLEN_S    |
                   ((mosi_bitlen - 1)  & SPI_USR_MOSI_BITLEN)    << SPI_USR_MOSI_BITLEN_S    |
                   ((dummy_bitlen - 1) & SPI_USR_DUMMY_CYCLELEN) << SPI_USR_DUMMY_CYCLELEN_S |
                   ((miso_bitlen - 1)  & SPI_USR_MISO_BITLEN)    << SPI_USR_MISO_BITLEN_S);

    // handle the transaction components
    if (cmd_bitlen > 0)
    {
        uint16 cmd = cmd_data << (16 - cmd_bitlen); // align to MSB
        cmd = (cmd >> 8) | (cmd << 8);              // swap byte order
        WRITE_PERI_REG(SPI_USER2(spi_no),
                       ((cmd_bitlen - 1 & SPI_USR_COMMAND_BITLEN) << SPI_USR_COMMAND_BITLEN_S) |
                       (cmd & SPI_USR_COMMAND_VALUE));
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_COMMAND);
    }
    if (addr_bitlen > 0)
    {
        WRITE_PERI_REG(SPI_ADDR(spi_no), addr_data << (32 - addr_bitlen));
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_ADDR);
    }
    if (mosi_bitlen > 0)
    {
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_MOSI);
    }
    if (dummy_bitlen > 0)
    {
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_DUMMY);
    }
    if (miso_bitlen > 0)
    {
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_MISO);
    }
    else if (miso_bitlen < 0)
    {
        SET_PERI_REG_MASK(SPI_USER(spi_no), SPI_DOUTDIN);
    }

    // start transaction
    SET_PERI_REG_MASK(SPI_CMD(spi_no), SPI_USR);

    while(READ_PERI_REG(SPI_CMD(spi_no)) & SPI_USR);
}
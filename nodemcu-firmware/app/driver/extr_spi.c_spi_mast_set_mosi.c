#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int uint16 ;
struct TYPE_2__ {int* word; unsigned long long dword; } ;
typedef  TYPE_1__ spi_buf_t ;

/* Variables and functions */
 int READ_PERI_REG (scalar_t__) ; 
 scalar_t__ SPI_CMD (int) ; 
 int SPI_USR ; 
 scalar_t__ SPI_W0 (int) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (scalar_t__,void*) ; 
 void* swap_endianess (int) ; 

void spi_mast_set_mosi(uint8 spi_no, uint16 offset, uint8 bitlen, uint32 data)
{
    spi_buf_t spi_buf;
    uint8     wn, shift;

    if (spi_no > 1)
        return; // handle invalid input number
    if (bitlen > 32)
        return; // handle invalid input number

    // determine which SPI_Wn register is addressed
    wn = offset >> 5;
    if (wn > 15) {
        return; // out of range
    }

    while(READ_PERI_REG(SPI_CMD(spi_no)) & SPI_USR);

    // transfer Wn to buf
    spi_buf.word[1] = READ_PERI_REG(SPI_W0(spi_no) + wn*4);
    spi_buf.word[1] = swap_endianess(spi_buf.word[1]);
    if (wn < 15) {
        spi_buf.word[0] = READ_PERI_REG(SPI_W0(spi_no) + (wn+1)*4);
        spi_buf.word[0] = swap_endianess(spi_buf.word[0]);
    }

    shift = 64 - (offset & 0x1f) - bitlen;
    spi_buf.dword &= ~((1ULL << bitlen)-1 << shift);
    spi_buf.dword |= (uint64)data << shift;

    if (wn < 15) {
        WRITE_PERI_REG(SPI_W0(spi_no) + (wn+1)*4, swap_endianess(spi_buf.word[0]));
    }
    WRITE_PERI_REG(SPI_W0(spi_no) + wn*4, swap_endianess(spi_buf.word[1]));

    return;
}
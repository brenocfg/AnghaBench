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
typedef  int u16 ;

/* Variables and functions */
 unsigned char IFX_SPI_MORE_BIT ; 
 unsigned char IFX_SPI_MORE_MASK ; 
 int IFX_SPI_PAYLOAD_SIZE ; 

__attribute__((used)) static void ifx_spi_setup_spi_header(unsigned char *txbuffer, int tx_count,
					unsigned char more)
{
	*(u16 *)(txbuffer) = tx_count;
	*(u16 *)(txbuffer+2) = IFX_SPI_PAYLOAD_SIZE;
	txbuffer[1] |= (more << IFX_SPI_MORE_BIT) & IFX_SPI_MORE_MASK;
}
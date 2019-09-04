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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rockchip_spi {int n_bytes; scalar_t__ rx; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_RXDR ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ rx_max (struct rockchip_spi*) ; 

__attribute__((used)) static void rockchip_spi_pio_reader(struct rockchip_spi *rs)
{
	u32 max = rx_max(rs);
	u32 rxw;

	while (max--) {
		rxw = readl_relaxed(rs->regs + ROCKCHIP_SPI_RXDR);
		if (rs->n_bytes == 1)
			*(u8 *)(rs->rx) = (u8)rxw;
		else
			*(u16 *)(rs->rx) = (u16)rxw;
		rs->rx += rs->n_bytes;
	}
}
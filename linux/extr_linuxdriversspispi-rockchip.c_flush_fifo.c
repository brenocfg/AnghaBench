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
struct rockchip_spi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_RXDR ; 
 scalar_t__ ROCKCHIP_SPI_RXFLR ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline void flush_fifo(struct rockchip_spi *rs)
{
	while (readl_relaxed(rs->regs + ROCKCHIP_SPI_RXFLR))
		readl_relaxed(rs->regs + ROCKCHIP_SPI_RXDR);
}
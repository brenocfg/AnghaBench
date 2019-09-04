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
typedef  int u32 ;
struct rockchip_spi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_TXFTLR ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static u32 get_fifo_len(struct rockchip_spi *rs)
{
	u32 fifo;

	for (fifo = 2; fifo < 32; fifo++) {
		writel_relaxed(fifo, rs->regs + ROCKCHIP_SPI_TXFTLR);
		if (fifo != readl_relaxed(rs->regs + ROCKCHIP_SPI_TXFTLR))
			break;
	}

	writel_relaxed(0, rs->regs + ROCKCHIP_SPI_TXFTLR);

	return (fifo == 31) ? 0 : fifo;
}
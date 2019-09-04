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
struct rockchip_spi {int rx_end; int rx; int n_bytes; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_RXFLR ; 
 int min (int,int) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 rx_max(struct rockchip_spi *rs)
{
	u32 rx_left = (rs->rx_end - rs->rx) / rs->n_bytes;
	u32 rx_room = (u32)readl_relaxed(rs->regs + ROCKCHIP_SPI_RXFLR);

	return min(rx_left, rx_room);
}
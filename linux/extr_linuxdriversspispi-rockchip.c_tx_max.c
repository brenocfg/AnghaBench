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
struct rockchip_spi {int tx_end; int tx; int n_bytes; int fifo_len; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_TXFLR ; 
 int min (int,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 tx_max(struct rockchip_spi *rs)
{
	u32 tx_left, tx_room;

	tx_left = (rs->tx_end - rs->tx) / rs->n_bytes;
	tx_room = rs->fifo_len - readl_relaxed(rs->regs + ROCKCHIP_SPI_TXFLR);

	return min(tx_left, tx_room);
}
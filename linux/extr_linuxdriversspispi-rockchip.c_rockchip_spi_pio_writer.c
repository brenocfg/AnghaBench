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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rockchip_spi {int n_bytes; scalar_t__ tx; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_TXDR ; 
 int /*<<< orphan*/  tx_max (struct rockchip_spi*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rockchip_spi_pio_writer(struct rockchip_spi *rs)
{
	u32 max = tx_max(rs);
	u32 txw = 0;

	while (max--) {
		if (rs->n_bytes == 1)
			txw = *(u8 *)(rs->tx);
		else
			txw = *(u16 *)(rs->tx);

		writel_relaxed(txw, rs->regs + ROCKCHIP_SPI_TXDR);
		rs->tx += rs->n_bytes;
	}
}
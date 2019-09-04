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
struct dw_spi {int n_bytes; scalar_t__ tx; scalar_t__ len; scalar_t__ tx_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SPI_DR ; 
 int /*<<< orphan*/  dw_write_io_reg (struct dw_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_max (struct dw_spi*) ; 

__attribute__((used)) static void dw_writer(struct dw_spi *dws)
{
	u32 max = tx_max(dws);
	u16 txw = 0;

	while (max--) {
		/* Set the tx word if the transfer's original "tx" is not null */
		if (dws->tx_end - dws->len) {
			if (dws->n_bytes == 1)
				txw = *(u8 *)(dws->tx);
			else
				txw = *(u16 *)(dws->tx);
		}
		dw_write_io_reg(dws, DW_SPI_DR, txw);
		dws->tx += dws->n_bytes;
	}
}
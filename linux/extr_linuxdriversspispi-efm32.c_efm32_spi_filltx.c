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
struct efm32_spi_ddata {scalar_t__ tx_len; scalar_t__ rx_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_STATUS ; 
 int REG_STATUS_TXBL ; 
 int efm32_spi_read32 (struct efm32_spi_ddata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_spi_tx_u8 (struct efm32_spi_ddata*) ; 

__attribute__((used)) static void efm32_spi_filltx(struct efm32_spi_ddata *ddata)
{
	while (ddata->tx_len &&
			ddata->tx_len + 2 > ddata->rx_len &&
			efm32_spi_read32(ddata, REG_STATUS) & REG_STATUS_TXBL) {
		efm32_spi_tx_u8(ddata);
	}
}
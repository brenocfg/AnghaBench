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
typedef  int /*<<< orphan*/  u8 ;
struct sdio_mmc_card {TYPE_1__* reg; int /*<<< orphan*/  tx_buf_size; int /*<<< orphan*/  func; } ;
struct mwifiex_adapter {int /*<<< orphan*/  tx_buf_size; struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_int_status_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  mwifiex_init_sdio_ioport (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_enable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_block_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_sdio_up_dev(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	u8 sdio_ireg;

	sdio_claim_host(card->func);
	sdio_enable_func(card->func);
	sdio_set_block_size(card->func, MWIFIEX_SDIO_BLOCK_SIZE);
	sdio_release_host(card->func);

	/* tx_buf_size might be changed to 3584 by firmware during
	 * data transfer, we will reset to default size.
	 */
	adapter->tx_buf_size = card->tx_buf_size;

	/* Read the host_int_status_reg for ACK the first interrupt got
	 * from the bootloader. If we don't do this we get a interrupt
	 * as soon as we register the irq.
	 */
	mwifiex_read_reg(adapter, card->reg->host_int_status_reg, &sdio_ireg);

	mwifiex_init_sdio_ioport(adapter);
}
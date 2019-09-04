#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int enabled; void* skb_arr; void* len_arr; int /*<<< orphan*/  pkt_aggr_limit; scalar_t__ start_port; scalar_t__ pkt_cnt; scalar_t__ buf_len; } ;
struct TYPE_3__ {int enabled; int /*<<< orphan*/  pkt_aggr_limit; scalar_t__ start_port; scalar_t__ pkt_cnt; scalar_t__ buf_len; } ;
struct sdio_mmc_card {scalar_t__ mp_tx_agg_buf_size; scalar_t__ mp_rx_agg_buf_size; int /*<<< orphan*/  can_ext_scan; int /*<<< orphan*/  can_auto_tdls; TYPE_2__ mpa_rx; TYPE_1__ mpa_tx; void* mp_regs; int /*<<< orphan*/  mp_agg_pkt_limit; int /*<<< orphan*/  mp_data_port_mask; int /*<<< orphan*/  curr_wr_port; int /*<<< orphan*/  curr_rd_port; scalar_t__ mp_wr_bitmap; scalar_t__ mp_rd_bitmap; struct mwifiex_sdio_card_reg* reg; int /*<<< orphan*/  func; } ;
struct mwifiex_sdio_card_reg {int /*<<< orphan*/  max_mp_regs; int /*<<< orphan*/  data_port_mask; int /*<<< orphan*/  start_wr_port; int /*<<< orphan*/  start_rd_port; int /*<<< orphan*/  host_int_status_reg; } ;
struct mwifiex_adapter {int host_disable_sdio_rx_aggr; int /*<<< orphan*/  ext_scan; int /*<<< orphan*/  auto_tdls; struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MWIFIEX_MP_AGGR_BUF_SIZE_32K ; 
 scalar_t__ MWIFIEX_MP_AGGR_BUF_SIZE_MAX ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwifiex_alloc_sdio_mpa_buffers (struct mwifiex_adapter*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_init_sdio_ioport (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_set_drvdata (int /*<<< orphan*/ ,struct sdio_mmc_card*) ; 

__attribute__((used)) static int mwifiex_init_sdio(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	const struct mwifiex_sdio_card_reg *reg = card->reg;
	int ret;
	u8 sdio_ireg;

	sdio_set_drvdata(card->func, card);

	/*
	 * Read the host_int_status_reg for ACK the first interrupt got
	 * from the bootloader. If we don't do this we get a interrupt
	 * as soon as we register the irq.
	 */
	mwifiex_read_reg(adapter, card->reg->host_int_status_reg, &sdio_ireg);

	/* Get SDIO ioport */
	mwifiex_init_sdio_ioport(adapter);

	/* Initialize SDIO variables in card */
	card->mp_rd_bitmap = 0;
	card->mp_wr_bitmap = 0;
	card->curr_rd_port = reg->start_rd_port;
	card->curr_wr_port = reg->start_wr_port;

	card->mp_data_port_mask = reg->data_port_mask;

	card->mpa_tx.buf_len = 0;
	card->mpa_tx.pkt_cnt = 0;
	card->mpa_tx.start_port = 0;

	card->mpa_tx.enabled = 1;
	card->mpa_tx.pkt_aggr_limit = card->mp_agg_pkt_limit;

	card->mpa_rx.buf_len = 0;
	card->mpa_rx.pkt_cnt = 0;
	card->mpa_rx.start_port = 0;

	card->mpa_rx.enabled = 1;
	card->mpa_rx.pkt_aggr_limit = card->mp_agg_pkt_limit;

	/* Allocate buffers for SDIO MP-A */
	card->mp_regs = kzalloc(reg->max_mp_regs, GFP_KERNEL);
	if (!card->mp_regs)
		return -ENOMEM;

	/* Allocate skb pointer buffers */
	card->mpa_rx.skb_arr = kcalloc(card->mp_agg_pkt_limit, sizeof(void *),
				       GFP_KERNEL);
	if (!card->mpa_rx.skb_arr) {
		kfree(card->mp_regs);
		return -ENOMEM;
	}

	card->mpa_rx.len_arr = kcalloc(card->mp_agg_pkt_limit,
				       sizeof(*card->mpa_rx.len_arr),
				       GFP_KERNEL);
	if (!card->mpa_rx.len_arr) {
		kfree(card->mp_regs);
		kfree(card->mpa_rx.skb_arr);
		return -ENOMEM;
	}

	ret = mwifiex_alloc_sdio_mpa_buffers(adapter,
					     card->mp_tx_agg_buf_size,
					     card->mp_rx_agg_buf_size);

	/* Allocate 32k MPA Tx/Rx buffers if 64k memory allocation fails */
	if (ret && (card->mp_tx_agg_buf_size == MWIFIEX_MP_AGGR_BUF_SIZE_MAX ||
		    card->mp_rx_agg_buf_size == MWIFIEX_MP_AGGR_BUF_SIZE_MAX)) {
		/* Disable rx single port aggregation */
		adapter->host_disable_sdio_rx_aggr = true;

		ret = mwifiex_alloc_sdio_mpa_buffers
			(adapter, MWIFIEX_MP_AGGR_BUF_SIZE_32K,
			 MWIFIEX_MP_AGGR_BUF_SIZE_32K);
		if (ret) {
			/* Disable multi port aggregation */
			card->mpa_tx.enabled = 0;
			card->mpa_rx.enabled = 0;
		}
	}

	adapter->auto_tdls = card->can_auto_tdls;
	adapter->ext_scan = card->can_ext_scan;
	return 0;
}
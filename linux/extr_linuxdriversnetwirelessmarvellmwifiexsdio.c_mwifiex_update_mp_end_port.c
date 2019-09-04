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
typedef  int u16 ;
struct sdio_mmc_card {int mp_end_port; int mp_data_port_mask; int max_ports; scalar_t__ curr_wr_port; struct mwifiex_sdio_card_reg* reg; } ;
struct mwifiex_sdio_card_reg {int data_port_mask; scalar_t__ start_wr_port; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
mwifiex_update_mp_end_port(struct mwifiex_adapter *adapter, u16 port)
{
	struct sdio_mmc_card *card = adapter->card;
	const struct mwifiex_sdio_card_reg *reg = card->reg;
	int i;

	card->mp_end_port = port;

	card->mp_data_port_mask = reg->data_port_mask;

	if (reg->start_wr_port) {
		for (i = 1; i <= card->max_ports - card->mp_end_port; i++)
			card->mp_data_port_mask &=
					~(1 << (card->max_ports - i));
	}

	card->curr_wr_port = reg->start_wr_port;

	mwifiex_dbg(adapter, CMD,
		    "cmd: mp_end_port %d, data port mask 0x%x\n",
		    port, card->mp_data_port_mask);
}
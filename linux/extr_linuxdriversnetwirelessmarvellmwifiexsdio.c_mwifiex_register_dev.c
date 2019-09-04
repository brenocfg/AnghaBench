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
struct sdio_mmc_card {scalar_t__ fw_dump_enh; int /*<<< orphan*/  firmware; struct sdio_func* func; int /*<<< orphan*/  tx_buf_size; struct mwifiex_adapter* adapter; } ;
struct sdio_func {int dummy; } ;
struct mwifiex_adapter {int num_mem_types; int /*<<< orphan*/  mem_type_mapping_tbl; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  tx_buf_size; struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MWIFIEX_SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  generic_mem_type_map ; 
 int /*<<< orphan*/  mem_type_mapping_tbl ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_register_dev(struct mwifiex_adapter *adapter)
{
	int ret;
	struct sdio_mmc_card *card = adapter->card;
	struct sdio_func *func = card->func;

	/* save adapter pointer in card */
	card->adapter = adapter;
	adapter->tx_buf_size = card->tx_buf_size;

	sdio_claim_host(func);

	/* Set block size */
	ret = sdio_set_block_size(card->func, MWIFIEX_SDIO_BLOCK_SIZE);
	sdio_release_host(func);
	if (ret) {
		mwifiex_dbg(adapter, ERROR,
			    "cannot set SDIO block size\n");
		return ret;
	}

	strcpy(adapter->fw_name, card->firmware);
	if (card->fw_dump_enh) {
		adapter->mem_type_mapping_tbl = generic_mem_type_map;
		adapter->num_mem_types = 1;
	} else {
		adapter->mem_type_mapping_tbl = mem_type_mapping_tbl;
		adapter->num_mem_types = ARRAY_SIZE(mem_type_mapping_tbl);
	}

	return 0;
}
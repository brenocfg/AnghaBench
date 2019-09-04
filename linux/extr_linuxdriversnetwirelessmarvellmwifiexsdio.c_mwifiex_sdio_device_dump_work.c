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
struct sdio_mmc_card {scalar_t__ fw_dump_enh; } ;
struct mwifiex_adapter {int /*<<< orphan*/  devdump_data; struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MWIFIEX_FW_DUMP_SIZE ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_drv_info_dump (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_prepare_fw_dump_info (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_sdio_fw_dump (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_sdio_generic_fw_dump (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_upload_device_dump (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_sdio_device_dump_work(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;

	adapter->devdump_data = vzalloc(MWIFIEX_FW_DUMP_SIZE);
	if (!adapter->devdump_data) {
		mwifiex_dbg(adapter, ERROR,
			    "vzalloc devdump data failure!\n");
		return;
	}

	mwifiex_drv_info_dump(adapter);
	if (card->fw_dump_enh)
		mwifiex_sdio_generic_fw_dump(adapter);
	else
		mwifiex_sdio_fw_dump(adapter);
	mwifiex_prepare_fw_dump_info(adapter);
	mwifiex_upload_device_dump(adapter);
}
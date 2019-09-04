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
struct sdio_mmc_card {TYPE_1__* reg; struct sdio_func* func; } ;
struct sdio_func {int dummy; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_int_enable; int /*<<< orphan*/  host_int_mask_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_sdio_interrupt ; 
 int mwifiex_write_reg_locked (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 

__attribute__((used)) static int mwifiex_sdio_enable_host_int(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	struct sdio_func *func = card->func;
	int ret;

	sdio_claim_host(func);

	/* Request the SDIO IRQ */
	ret = sdio_claim_irq(func, mwifiex_sdio_interrupt);
	if (ret) {
		mwifiex_dbg(adapter, ERROR,
			    "claim irq failed: ret=%d\n", ret);
		goto out;
	}

	/* Simply write the mask to the register */
	ret = mwifiex_write_reg_locked(func, card->reg->host_int_mask_reg,
				       card->reg->host_int_enable);
	if (ret) {
		mwifiex_dbg(adapter, ERROR,
			    "enable host interrupt failed\n");
		sdio_release_irq(func);
	}

out:
	sdio_release_host(func);
	return ret;
}
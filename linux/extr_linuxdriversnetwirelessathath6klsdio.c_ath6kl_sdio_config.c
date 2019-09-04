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
struct sdio_func {int enable_timeout; int /*<<< orphan*/  card; } ;
struct ath6kl_sdio {TYPE_1__* id; struct sdio_func* func; } ;
struct ath6kl {int dummy; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  CCCR_SDIO_IRQ_MODE_REG ; 
 int /*<<< orphan*/  HIF_MBOX_BLOCK_SIZE ; 
 int MANUFACTURER_ID_AR6003_BASE ; 
 int MANUFACTURER_ID_ATH6KL_BASE_MASK ; 
 int /*<<< orphan*/  SDIO_IRQ_MODE_ASYNC_4BIT_IRQ ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int,...) ; 
 int ath6kl_sdio_func0_cmd52_wr_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_sdio_config(struct ath6kl *ar)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	struct sdio_func *func = ar_sdio->func;
	int ret;

	sdio_claim_host(func);

	if ((ar_sdio->id->device & MANUFACTURER_ID_ATH6KL_BASE_MASK) >=
	    MANUFACTURER_ID_AR6003_BASE) {
		/* enable 4-bit ASYNC interrupt on AR6003 or later */
		ret = ath6kl_sdio_func0_cmd52_wr_byte(func->card,
						CCCR_SDIO_IRQ_MODE_REG,
						SDIO_IRQ_MODE_ASYNC_4BIT_IRQ);
		if (ret) {
			ath6kl_err("Failed to enable 4-bit async irq mode %d\n",
				   ret);
			goto out;
		}

		ath6kl_dbg(ATH6KL_DBG_BOOT, "4-bit async irq mode enabled\n");
	}

	/* give us some time to enable, in ms */
	func->enable_timeout = 100;

	ret = sdio_set_block_size(func, HIF_MBOX_BLOCK_SIZE);
	if (ret) {
		ath6kl_err("Set sdio block size %d failed: %d)\n",
			   HIF_MBOX_BLOCK_SIZE, ret);
		goto out;
	}

out:
	sdio_release_host(func);

	return ret;
}
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
struct TYPE_2__ {int /*<<< orphan*/  host_int_mask_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_write_reg_locked (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 

__attribute__((used)) static void mwifiex_sdio_disable_host_int(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	struct sdio_func *func = card->func;

	sdio_claim_host(func);
	mwifiex_write_reg_locked(func, card->reg->host_int_mask_reg, 0);
	sdio_release_irq(func);
	sdio_release_host(func);
}
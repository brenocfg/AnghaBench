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
struct sdio_mmc_card {int /*<<< orphan*/  func; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int mwifiex_write_reg_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_write_reg(struct mwifiex_adapter *adapter, u32 reg, u8 data)
{
	struct sdio_mmc_card *card = adapter->card;
	int ret;

	sdio_claim_host(card->func);
	ret = mwifiex_write_reg_locked(card->func, reg, data);
	sdio_release_host(card->func);

	return ret;
}
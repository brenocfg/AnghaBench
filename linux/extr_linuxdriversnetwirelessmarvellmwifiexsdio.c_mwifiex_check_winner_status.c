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
typedef  scalar_t__ u8 ;
struct sdio_mmc_card {TYPE_1__* reg; } ;
struct mwifiex_adapter {int winner; struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_reg_0; } ;

/* Variables and functions */
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int mwifiex_check_winner_status(struct mwifiex_adapter *adapter)
{
	int ret = 0;
	u8 winner = 0;
	struct sdio_mmc_card *card = adapter->card;

	if (mwifiex_read_reg(adapter, card->reg->status_reg_0, &winner))
		return -1;

	if (winner)
		adapter->winner = 0;
	else
		adapter->winner = 1;

	return ret;
}
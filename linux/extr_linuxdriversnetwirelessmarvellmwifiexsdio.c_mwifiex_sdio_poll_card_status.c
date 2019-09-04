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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sdio_mmc_card {TYPE_1__* reg; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MAX_POLL_TRIES ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
mwifiex_sdio_poll_card_status(struct mwifiex_adapter *adapter, u8 bits)
{
	struct sdio_mmc_card *card = adapter->card;
	u32 tries;
	u8 cs;

	for (tries = 0; tries < MAX_POLL_TRIES; tries++) {
		if (mwifiex_read_reg(adapter, card->reg->poll_reg, &cs))
			break;
		else if ((cs & bits) == bits)
			return 0;

		usleep_range(10, 20);
	}

	mwifiex_dbg(adapter, ERROR,
		    "poll card status failed, tries = %d\n", tries);

	return -1;
}
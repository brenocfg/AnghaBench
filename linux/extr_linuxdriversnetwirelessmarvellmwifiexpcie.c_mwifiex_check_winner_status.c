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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int /*<<< orphan*/  fw_status; } ;
struct mwifiex_adapter {int winner; struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
mwifiex_check_winner_status(struct mwifiex_adapter *adapter)
{
	u32 winner = 0;
	int ret = 0;
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	if (mwifiex_read_reg(adapter, reg->fw_status, &winner)) {
		ret = -1;
	} else if (!winner) {
		mwifiex_dbg(adapter, INFO, "PCI-E is the winner\n");
		adapter->winner = 1;
	} else {
		mwifiex_dbg(adapter, ERROR,
			    "PCI-E is not the winner <%#x>", winner);
	}

	return ret;
}
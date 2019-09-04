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
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {scalar_t__ sleep_cookie; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_pcie_delete_cmdrsp_buf (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_evtbd_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_rxbd_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_sleep_cookie_buf (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_txbd_ring (struct mwifiex_adapter*) ; 

__attribute__((used)) static void mwifiex_pcie_free_buffers(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	if (reg->sleep_cookie)
		mwifiex_pcie_delete_sleep_cookie_buf(adapter);

	mwifiex_pcie_delete_cmdrsp_buf(adapter);
	mwifiex_pcie_delete_evtbd_ring(adapter);
	mwifiex_pcie_delete_rxbd_ring(adapter);
	mwifiex_pcie_delete_txbd_ring(adapter);
}
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
struct pcie_service_card {int txbd_flush; int /*<<< orphan*/  txbd_rdptr; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_INTR_DNLD_RDY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PCIE_CPU_INT_EVENT ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_pcie_txbd_empty (struct pcie_service_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_clean_pcie_ring_buf(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;

	if (!mwifiex_pcie_txbd_empty(card, card->txbd_rdptr)) {
		card->txbd_flush = 1;
		/* write pointer already set at last send
		 * send dnld-rdy intr again, wait for completion.
		 */
		if (mwifiex_write_reg(adapter, PCIE_CPU_INT_EVENT,
				      CPU_INTR_DNLD_RDY)) {
			mwifiex_dbg(adapter, ERROR,
				    "failed to assert dnld-rdy interrupt.\n");
			return -1;
		}
	}
	return 0;
}
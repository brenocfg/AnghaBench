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
struct pcie_service_card {int /*<<< orphan*/  dev; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_try_reset_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_pcie_card_reset_work(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;

	/* We can't afford to wait here; remove() might be waiting on us. If we
	 * can't grab the device lock, maybe we'll get another chance later.
	 */
	pci_try_reset_function(card->dev);
}
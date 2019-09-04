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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_service_card {int /*<<< orphan*/  sleep_cookie_vbase; int /*<<< orphan*/  sleep_cookie_pbase; int /*<<< orphan*/  dev; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FW_AWAKE_COOKIE ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pcie_alloc_sleep_cookie_buf(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	u32 tmp;

	card->sleep_cookie_vbase = pci_alloc_consistent(card->dev, sizeof(u32),
						     &card->sleep_cookie_pbase);
	if (!card->sleep_cookie_vbase) {
		mwifiex_dbg(adapter, ERROR,
			    "pci_alloc_consistent failed!\n");
		return -ENOMEM;
	}
	/* Init val of Sleep Cookie */
	tmp = FW_AWAKE_COOKIE;
	put_unaligned(tmp, card->sleep_cookie_vbase);

	mwifiex_dbg(adapter, INFO,
		    "alloc_scook: sleep cookie=0x%x\n",
		    get_unaligned(card->sleep_cookie_vbase));

	return 0;
}
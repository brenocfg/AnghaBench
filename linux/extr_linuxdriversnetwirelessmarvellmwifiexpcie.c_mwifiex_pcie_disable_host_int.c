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
struct mwifiex_adapter {int /*<<< orphan*/  tx_hw_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PCIE_HOST_INT_MASK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_pcie_ok_to_access_hw (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_pcie_disable_host_int(struct mwifiex_adapter *adapter)
{
	if (mwifiex_pcie_ok_to_access_hw(adapter)) {
		if (mwifiex_write_reg(adapter, PCIE_HOST_INT_MASK,
				      0x00000000)) {
			mwifiex_dbg(adapter, ERROR,
				    "Disable host interrupt failed\n");
			return -1;
		}
	}

	atomic_set(&adapter->tx_hw_pending, 0);
	return 0;
}
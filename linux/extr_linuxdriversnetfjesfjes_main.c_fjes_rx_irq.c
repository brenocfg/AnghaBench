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
struct fjes_hw {int dummy; } ;
struct fjes_adapter {int unset_rx_last; int /*<<< orphan*/  napi; struct fjes_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ICTL_MASK_RX_DATA ; 
 int /*<<< orphan*/  fjes_hw_set_irqmask (struct fjes_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fjes_rx_irq(struct fjes_adapter *adapter, int src_epid)
{
	struct fjes_hw *hw = &adapter->hw;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_RX_DATA, true);

	adapter->unset_rx_last = true;
	napi_schedule(&adapter->napi);
}
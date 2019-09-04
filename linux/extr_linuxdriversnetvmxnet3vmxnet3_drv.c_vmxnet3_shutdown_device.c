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
struct vmxnet3_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  cmd_lock; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_QUIESCE_DEV ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_STATE_BIT_QUIESCED ; 
 int /*<<< orphan*/  VMXNET3_STATE_BIT_RESETTING ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vmxnet3_disable_all_intrs (struct vmxnet3_adapter*) ; 

__attribute__((used)) static void vmxnet3_shutdown_device(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;

	/* Reset_work may be in the middle of resetting the device, wait for its
	 * completion.
	 */
	while (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	if (test_and_set_bit(VMXNET3_STATE_BIT_QUIESCED,
			     &adapter->state)) {
		clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
		return;
	}
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_QUIESCE_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	vmxnet3_disable_all_intrs(adapter);

	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
}
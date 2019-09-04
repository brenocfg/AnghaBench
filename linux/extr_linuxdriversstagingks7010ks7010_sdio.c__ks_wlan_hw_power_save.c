#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  snooze_guard; int /*<<< orphan*/  confirm_wait; } ;
struct TYPE_3__ {scalar_t__ power_mgmt; scalar_t__ operation_mode; } ;
struct ks_wlan_private {scalar_t__ dev_state; int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; TYPE_2__ psstatus; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  connect_status; TYPE_1__ reg; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_SLEEP ; 
 int /*<<< orphan*/  GCR_B_DOZE ; 
 int /*<<< orphan*/  GCR_B_REG ; 
 int /*<<< orphan*/  INT_PENDING_REG ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 scalar_t__ POWER_MGMT_ACTIVE ; 
 scalar_t__ PS_SNOOZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  is_connect_status (int /*<<< orphan*/ ) ; 
 int ks7010_sdio_readb (struct ks_wlan_private*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ks7010_sdio_writeb (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  txq_count (struct ks_wlan_private*) ; 
 scalar_t__ txq_has_space (struct ks_wlan_private*) ; 

__attribute__((used)) static void _ks_wlan_hw_power_save(struct ks_wlan_private *priv)
{
	u8 byte;
	int ret;

	if (priv->reg.power_mgmt == POWER_MGMT_ACTIVE)
		return;

	if (priv->reg.operation_mode != MODE_INFRASTRUCTURE)
		return;

	if (!is_connect_status(priv->connect_status))
		return;

	if (priv->dev_state != DEVICE_STATE_SLEEP)
		return;

	if (atomic_read(&priv->psstatus.status) == PS_SNOOZE)
		return;

	netdev_dbg(priv->net_dev,
		   "STATUS:\n"
		   "- psstatus.status = %d\n"
		   "- psstatus.confirm_wait = %d\n"
		   "- psstatus.snooze_guard = %d\n"
		   "- txq_count = %d\n",
		   atomic_read(&priv->psstatus.status),
		   atomic_read(&priv->psstatus.confirm_wait),
		   atomic_read(&priv->psstatus.snooze_guard),
		   txq_count(priv));

	if (atomic_read(&priv->psstatus.confirm_wait) ||
	    atomic_read(&priv->psstatus.snooze_guard) ||
	    txq_has_space(priv)) {
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
		return;
	}

	ret = ks7010_sdio_readb(priv, INT_PENDING_REG, &byte);
	if (ret) {
		netdev_err(priv->net_dev, "read INT_PENDING_REG\n");
		goto queue_delayed_work;
	}
	if (byte)
		goto queue_delayed_work;

	ret = ks7010_sdio_writeb(priv, GCR_B_REG, GCR_B_DOZE);
	if (ret) {
		netdev_err(priv->net_dev, "write GCR_B_REG\n");
		goto queue_delayed_work;
	}
	atomic_set(&priv->psstatus.status, PS_SNOOZE);

	return;

queue_delayed_work:
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
}
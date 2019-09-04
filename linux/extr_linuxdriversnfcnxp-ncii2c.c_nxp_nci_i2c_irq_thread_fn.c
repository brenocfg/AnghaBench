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
struct sk_buff {int dummy; } ;
struct nxp_nci_info {int mode; int /*<<< orphan*/  info_lock; } ;
struct nxp_nci_i2c_phy {int hard_fault; int /*<<< orphan*/  ndev; struct i2c_client* i2c_dev; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  NXP_NCI_MODE_COLD 130 
#define  NXP_NCI_MODE_FW 129 
#define  NXP_NCI_MODE_NCI 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nxp_nci_info* nci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nxp_nci_fw_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int nxp_nci_i2c_fw_read (struct nxp_nci_i2c_phy*,struct sk_buff**) ; 
 int nxp_nci_i2c_nci_read (struct nxp_nci_i2c_phy*,struct sk_buff**) ; 

__attribute__((used)) static irqreturn_t nxp_nci_i2c_irq_thread_fn(int irq, void *phy_id)
{
	struct nxp_nci_i2c_phy *phy = phy_id;
	struct i2c_client *client;
	struct nxp_nci_info *info;

	struct sk_buff *skb = NULL;
	int r = 0;

	if (!phy || !phy->ndev)
		goto exit_irq_none;

	client = phy->i2c_dev;

	if (!client || irq != client->irq)
		goto exit_irq_none;

	info = nci_get_drvdata(phy->ndev);

	if (!info)
		goto exit_irq_none;

	mutex_lock(&info->info_lock);

	if (phy->hard_fault != 0)
		goto exit_irq_handled;

	switch (info->mode) {
	case NXP_NCI_MODE_NCI:
		r = nxp_nci_i2c_nci_read(phy, &skb);
		break;
	case NXP_NCI_MODE_FW:
		r = nxp_nci_i2c_fw_read(phy, &skb);
		break;
	case NXP_NCI_MODE_COLD:
		r = -EREMOTEIO;
		break;
	}

	if (r == -EREMOTEIO) {
		phy->hard_fault = r;
		skb = NULL;
	} else if (r < 0) {
		nfc_err(&client->dev, "Read failed with error %d\n", r);
		goto exit_irq_handled;
	}

	switch (info->mode) {
	case NXP_NCI_MODE_NCI:
		nci_recv_frame(phy->ndev, skb);
		break;
	case NXP_NCI_MODE_FW:
		nxp_nci_fw_recv_frame(phy->ndev, skb);
		break;
	case NXP_NCI_MODE_COLD:
		break;
	}

exit_irq_handled:
	mutex_unlock(&info->info_lock);
	return IRQ_HANDLED;
exit_irq_none:
	WARN_ON_ONCE(1);
	return IRQ_NONE;
}
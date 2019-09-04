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
struct sk_buff {int dummy; } ;
struct microread_i2c_phy {int hard_fault; int /*<<< orphan*/  hdev; TYPE_1__* i2c_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int microread_i2c_read (struct microread_i2c_phy*,struct sk_buff**) ; 
 int /*<<< orphan*/  nfc_hci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static irqreturn_t microread_i2c_irq_thread_fn(int irq, void *phy_id)
{
	struct microread_i2c_phy *phy = phy_id;
	struct sk_buff *skb = NULL;
	int r;

	if (!phy || irq != phy->i2c_dev->irq) {
		WARN_ON_ONCE(1);
		return IRQ_NONE;
	}

	if (phy->hard_fault != 0)
		return IRQ_HANDLED;

	r = microread_i2c_read(phy, &skb);
	if (r == -EREMOTEIO) {
		phy->hard_fault = r;

		nfc_hci_recv_frame(phy->hdev, NULL);

		return IRQ_HANDLED;
	} else if ((r == -ENOMEM) || (r == -EBADMSG)) {
		return IRQ_HANDLED;
	}

	nfc_hci_recv_frame(phy->hdev, skb);

	return IRQ_HANDLED;
}
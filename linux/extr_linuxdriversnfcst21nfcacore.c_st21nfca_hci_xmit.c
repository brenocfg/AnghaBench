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
struct st21nfca_hci_info {int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {int dummy; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int st21nfca_hci_xmit(struct nfc_hci_dev *hdev, struct sk_buff *skb)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	return info->phy_ops->write(info->phy_id, skb);
}
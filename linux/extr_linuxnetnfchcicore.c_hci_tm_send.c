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
struct nfc_hci_dev {TYPE_1__* ops; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int (* tm_send ) (struct nfc_hci_dev*,struct sk_buff*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int stub1 (struct nfc_hci_dev*,struct sk_buff*) ; 

__attribute__((used)) static int hci_tm_send(struct nfc_dev *nfc_dev, struct sk_buff *skb)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	if (!hdev->ops->tm_send) {
		kfree_skb(skb);
		return -ENOTSUPP;
	}

	return hdev->ops->tm_send(hdev, skb);
}
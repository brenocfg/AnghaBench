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
struct nfc_llcp_local {int dummy; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __nfc_llcp_recv (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 

int nfc_llcp_data_received(struct nfc_dev *dev, struct sk_buff *skb)
{
	struct nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	if (local == NULL) {
		kfree_skb(skb);
		return -ENODEV;
	}

	__nfc_llcp_recv(local, skb);

	return 0;
}
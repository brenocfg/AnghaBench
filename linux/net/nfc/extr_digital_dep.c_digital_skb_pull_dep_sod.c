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
typedef  int u8 ;
struct sk_buff {int len; int* data; } ;
struct nfc_digital_dev {scalar_t__ curr_rf_tech; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ NFC_DIGITAL_RF_TECH_106A ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int digital_skb_pull_dep_sod(struct nfc_digital_dev *ddev,
				    struct sk_buff *skb)
{
	u8 size;

	if (skb->len < 2)
		return -EIO;

	if (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)
		skb_pull(skb, sizeof(u8));

	size = skb->data[0];
	if (size != skb->len)
		return -EIO;

	skb_pull(skb, sizeof(u8));

	return 0;
}
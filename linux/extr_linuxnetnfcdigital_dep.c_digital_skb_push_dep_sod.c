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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct nfc_digital_dev {scalar_t__ curr_rf_tech; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_NFC_DEP_NFCA_SOD_SB ; 
 scalar_t__ NFC_DIGITAL_RF_TECH_106A ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void digital_skb_push_dep_sod(struct nfc_digital_dev *ddev,
				     struct sk_buff *skb)
{
	skb_push(skb, sizeof(u8));

	skb->data[0] = skb->len;

	if (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)
		*(u8 *)skb_push(skb, sizeof(u8)) = DIGITAL_NFC_DEP_NFCA_SOD_SB;
}
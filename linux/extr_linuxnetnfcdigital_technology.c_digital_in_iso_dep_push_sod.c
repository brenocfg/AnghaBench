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
struct sk_buff {scalar_t__ len; int* data; } ;
struct nfc_digital_dev {scalar_t__ target_fsc; int curr_nfc_dep_pni; } ;

/* Variables and functions */
 int DIGITAL_ISO_DEP_I_PCB ; 
 int DIGITAL_ISO_DEP_PNI (int) ; 
 int EIO ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

int digital_in_iso_dep_push_sod(struct nfc_digital_dev *ddev,
				struct sk_buff *skb)
{
	/*
	 * Chaining not supported so skb->len + 1 PCB byte + 2 CRC bytes must
	 * not be greater than remote FSC
	 */
	if (skb->len + 3 > ddev->target_fsc)
		return -EIO;

	skb_push(skb, 1);

	*skb->data = DIGITAL_ISO_DEP_I_PCB | ddev->curr_nfc_dep_pni;

	ddev->curr_nfc_dep_pni =
		DIGITAL_ISO_DEP_PNI(ddev->curr_nfc_dep_pni + 1);

	return 0;
}
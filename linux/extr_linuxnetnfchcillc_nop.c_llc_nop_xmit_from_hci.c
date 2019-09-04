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
struct nfc_llc {int dummy; } ;
struct llc_nop {int (* xmit_to_drv ) (int /*<<< orphan*/ ,struct sk_buff*) ;int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 struct llc_nop* nfc_llc_get_data (struct nfc_llc*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int llc_nop_xmit_from_hci(struct nfc_llc *llc, struct sk_buff *skb)
{
	struct llc_nop *llc_nop = nfc_llc_get_data(llc);

	return llc_nop->xmit_to_drv(llc_nop->hdev, skb);
}
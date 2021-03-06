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
struct llc_nop {int /*<<< orphan*/  hdev; int /*<<< orphan*/  (* rcv_to_hci ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 struct llc_nop* nfc_llc_get_data (struct nfc_llc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void llc_nop_rcv_from_drv(struct nfc_llc *llc, struct sk_buff *skb)
{
	struct llc_nop *llc_nop = nfc_llc_get_data(llc);

	llc_nop->rcv_to_hci(llc_nop->hdev, skb);
}
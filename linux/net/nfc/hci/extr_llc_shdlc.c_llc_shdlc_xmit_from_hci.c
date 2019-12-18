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
struct llc_shdlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  send_q; } ;

/* Variables and functions */
 struct llc_shdlc* nfc_llc_get_data (struct nfc_llc*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int llc_shdlc_xmit_from_hci(struct nfc_llc *llc, struct sk_buff *skb)
{
	struct llc_shdlc *shdlc = nfc_llc_get_data(llc);

	skb_queue_tail(&shdlc->send_q, skb);

	schedule_work(&shdlc->sm_work);

	return 0;
}
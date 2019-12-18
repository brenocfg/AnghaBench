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
struct nfc_llc {int dummy; } ;
struct llc_shdlc {int /*<<< orphan*/  ack_pending_q; int /*<<< orphan*/  send_q; int /*<<< orphan*/  rcv_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct llc_shdlc*) ; 
 struct llc_shdlc* nfc_llc_get_data (struct nfc_llc*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_shdlc_deinit(struct nfc_llc *llc)
{
	struct llc_shdlc *shdlc = nfc_llc_get_data(llc);

	skb_queue_purge(&shdlc->rcv_q);
	skb_queue_purge(&shdlc->send_q);
	skb_queue_purge(&shdlc->ack_pending_q);

	kfree(shdlc);
}
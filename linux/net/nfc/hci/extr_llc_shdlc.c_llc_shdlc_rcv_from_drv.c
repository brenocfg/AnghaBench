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
struct llc_shdlc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_shdlc_recv_frame (struct llc_shdlc*,struct sk_buff*) ; 
 struct llc_shdlc* nfc_llc_get_data (struct nfc_llc*) ; 

__attribute__((used)) static void llc_shdlc_rcv_from_drv(struct nfc_llc *llc, struct sk_buff *skb)
{
	struct llc_shdlc *shdlc = nfc_llc_get_data(llc);

	llc_shdlc_recv_frame(shdlc, skb);
}
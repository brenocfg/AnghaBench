#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  lsap; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  lsap; } ;
struct llc_sap_state_ev {TYPE_2__ daddr; TYPE_1__ saddr; } ;
struct llc_sap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_test_cmd (struct sk_buff*) ; 
 struct llc_sap_state_ev* llc_sap_ev (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 

int llc_sap_action_send_test_c(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	int rc;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, ev->saddr.lsap,
			    ev->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_test_cmd(skb);
	rc = llc_mac_hdr_init(skb, ev->saddr.mac, ev->daddr.mac);
	if (likely(!rc)) {
		skb_get(skb);
		rc = dev_queue_xmit(skb);
	}
	return rc;
}
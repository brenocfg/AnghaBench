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
struct sk_buff {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lsap; } ;
struct llc_sap {TYPE_1__ laddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_ui_cmd (struct sk_buff*) ; 

int llc_build_and_send_ui_pkt(struct llc_sap *sap, struct sk_buff *skb,
			      unsigned char *dmac, unsigned char dsap)
{
	int rc;
	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, sap->laddr.lsap,
			    dsap, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(skb);
	rc = llc_mac_hdr_init(skb, skb->dev->dev_addr, dmac);
	if (likely(!rc))
		rc = dev_queue_xmit(skb);
	return rc;
}
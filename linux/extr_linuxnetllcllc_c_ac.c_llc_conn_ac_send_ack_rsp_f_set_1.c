#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  lsap; } ;
struct llc_sock {TYPE_2__ daddr; TYPE_3__* dev; int /*<<< orphan*/  vR; struct llc_sap* sap; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsap; } ;
struct llc_sap {TYPE_1__ laddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  LLC_PDU_RSP ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_S ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* llc_alloc_frame (struct sock*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_conn_send_pdu (struct sock*,struct sk_buff*) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_rr_rsp (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

int llc_conn_ac_send_ack_rsp_f_set_1(struct sock *sk, struct sk_buff *skb)
{
	int rc = -ENOBUFS;
	struct llc_sock *llc = llc_sk(sk);
	struct sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_S, 0);

	if (nskb) {
		struct llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_S, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 1, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		if (unlikely(rc))
			goto free;
		llc_conn_send_pdu(sk, nskb);
	}
out:
	return rc;
free:
	kfree_skb(nskb);
	goto out;
}
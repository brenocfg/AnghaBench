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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lsap; int /*<<< orphan*/ * mac; } ;
struct llc_sock {TYPE_3__* dev; TYPE_2__ daddr; struct llc_sap* sap; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsap; } ;
struct llc_sap {TYPE_1__ laddr; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* llc_alloc_frame (struct sock*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_conn_send_pdu (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  llc_conn_set_p_flag (struct sock*,int) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_sabme_cmd (struct sk_buff*,int) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

int llc_conn_ac_send_sabme_cmd_p_set_x(struct sock *sk, struct sk_buff *skb)
{
	int rc = -ENOBUFS;
	struct llc_sock *llc = llc_sk(sk);
	struct sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	if (nskb) {
		struct llc_sap *sap = llc->sap;
		u8 *dmac = llc->daddr.mac;

		if (llc->dev->flags & IFF_LOOPBACK)
			dmac = llc->dev->dev_addr;
		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_CMD);
		llc_pdu_init_as_sabme_cmd(nskb, 1);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, dmac);
		if (unlikely(rc))
			goto free;
		llc_conn_send_pdu(sk, nskb);
		llc_conn_set_p_flag(sk, 1);
	}
out:
	return rc;
free:
	kfree_skb(nskb);
	goto out;
}
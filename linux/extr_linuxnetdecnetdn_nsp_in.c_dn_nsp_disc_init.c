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
typedef  int u16 ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_2__* sk_socket; int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int len; int* data; } ;
struct dn_skb_cb {scalar_t__ src_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  opt_data; void* opt_optl; void* opt_status; } ;
struct dn_scp {int state; int /*<<< orphan*/  persist; int /*<<< orphan*/  persist_fxn; scalar_t__ addrrem; TYPE_1__ discdata_in; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
#define  DN_CD 131 
#define  DN_CI 130 
#define  DN_DI 129 
 int DN_DIC ; 
 int DN_DN ; 
 int DN_RJ ; 
#define  DN_RUN 128 
 struct dn_scp* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NSP_DISCCONF ; 
 int /*<<< orphan*/  NSP_REASON_DC ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ SS_UNCONNECTED ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dn_destroy_timer ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_send_disc (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_nsp_disc_init(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	unsigned short reason;

	if (skb->len < 2)
		goto out;

	reason = le16_to_cpu(*(__le16 *)skb->data);
	skb_pull(skb, 2);

	scp->discdata_in.opt_status = cpu_to_le16(reason);
	scp->discdata_in.opt_optl   = 0;
	memset(scp->discdata_in.opt_data, 0, 16);

	if (skb->len > 0) {
		u16 dlen = *skb->data;
		if ((dlen <= 16) && (dlen <= skb->len)) {
			scp->discdata_in.opt_optl = cpu_to_le16(dlen);
			skb_copy_from_linear_data_offset(skb, 1, scp->discdata_in.opt_data, dlen);
		}
	}

	scp->addrrem = cb->src_port;
	sk->sk_state = TCP_CLOSE;

	switch (scp->state) {
	case DN_CI:
	case DN_CD:
		scp->state = DN_RJ;
		sk->sk_err = ECONNREFUSED;
		break;
	case DN_RUN:
		sk->sk_shutdown |= SHUTDOWN_MASK;
		scp->state = DN_DN;
		break;
	case DN_DI:
		scp->state = DN_DIC;
		break;
	}

	if (!sock_flag(sk, SOCK_DEAD)) {
		if (sk->sk_socket->state != SS_UNCONNECTED)
			sk->sk_socket->state = SS_DISCONNECTING;
		sk->sk_state_change(sk);
	}

	/*
	 * It appears that its possible for remote machines to send disc
	 * init messages with no port identifier if we are in the CI and
	 * possibly also the CD state. Obviously we shouldn't reply with
	 * a message if we don't know what the end point is.
	 */
	if (scp->addrrem) {
		dn_nsp_send_disc(sk, NSP_DISCCONF, NSP_REASON_DC, GFP_ATOMIC);
	}
	scp->persist_fxn = dn_destroy_timer;
	scp->persist = dn_nsp_persist(sk);

out:
	kfree_skb(skb);
}
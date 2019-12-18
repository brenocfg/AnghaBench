#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int len; unsigned char* data; } ;
struct dn_skb_cb {int services; int /*<<< orphan*/  segsize; int /*<<< orphan*/  info; int /*<<< orphan*/  src_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  opt_data; int /*<<< orphan*/  opt_optl; } ;
struct dn_scp {scalar_t__ state; int services_rem; TYPE_1__ conndata_in; int /*<<< orphan*/  max_window; int /*<<< orphan*/  segsize_rem; int /*<<< orphan*/  info_rem; int /*<<< orphan*/  addrrem; scalar_t__ persist; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ DN_CD ; 
 scalar_t__ DN_CI ; 
 int /*<<< orphan*/  DN_NOCHANGE ; 
 scalar_t__ DN_RUN ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int NSP_FC_MASK ; 
 int NSP_FC_NONE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  decnet_no_fc_max_cwnd ; 
 int /*<<< orphan*/  dn_nsp_send_link (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_nsp_conn_conf(struct sock *sk, struct sk_buff *skb)
{
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	struct dn_scp *scp = DN_SK(sk);
	unsigned char *ptr;

	if (skb->len < 4)
		goto out;

	ptr = skb->data;
	cb->services = *ptr++;
	cb->info = *ptr++;
	cb->segsize = le16_to_cpu(*(__le16 *)ptr);

	if ((scp->state == DN_CI) || (scp->state == DN_CD)) {
		scp->persist = 0;
		scp->addrrem = cb->src_port;
		sk->sk_state = TCP_ESTABLISHED;
		scp->state = DN_RUN;
		scp->services_rem = cb->services;
		scp->info_rem = cb->info;
		scp->segsize_rem = cb->segsize;

		if ((scp->services_rem & NSP_FC_MASK) == NSP_FC_NONE)
			scp->max_window = decnet_no_fc_max_cwnd;

		if (skb->len > 0) {
			u16 dlen = *skb->data;
			if ((dlen <= 16) && (dlen <= skb->len)) {
				scp->conndata_in.opt_optl = cpu_to_le16(dlen);
				skb_copy_from_linear_data_offset(skb, 1,
					      scp->conndata_in.opt_data, dlen);
			}
		}
		dn_nsp_send_link(sk, DN_NOCHANGE, 0);
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	}

out:
	kfree_skb(skb);
}
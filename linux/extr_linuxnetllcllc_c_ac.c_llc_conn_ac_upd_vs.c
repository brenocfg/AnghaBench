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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_sn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  X; int /*<<< orphan*/  vS; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDU_SUPV_GET_Nr (struct llc_pdu_sn*) ; 
 scalar_t__ llc_circular_between (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_conn_ac_set_vs_nr (struct sock*,struct sk_buff*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 TYPE_1__* llc_sk (struct sock*) ; 

int llc_conn_ac_upd_vs(struct sock *sk, struct sk_buff *skb)
{
	struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	u8 nr = PDU_SUPV_GET_Nr(pdu);

	if (llc_circular_between(llc_sk(sk)->vS, nr, llc_sk(sk)->X))
		llc_conn_ac_set_vs_nr(sk, skb);
	return 0;
}
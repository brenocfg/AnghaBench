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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_sn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_I_GET_NR (struct llc_pdu_sn*) ; 
 int /*<<< orphan*/  llc_conn_resend_i_pdu_as_cmd (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 

int llc_conn_ac_resend_i_xxx_x_set_0(struct sock *sk, struct sk_buff *skb)
{
	struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	u8 nr = LLC_I_GET_NR(pdu);

	llc_conn_resend_i_pdu_as_cmd(sk, nr, 0);
	return 0;
}
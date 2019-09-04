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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_sn {int dummy; } ;
struct TYPE_2__ {scalar_t__ vR; int /*<<< orphan*/  rw; } ;

/* Variables and functions */
 scalar_t__ LLC_I_GET_NS (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_I_PF_IS_1 (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_PDU_IS_RSP (struct llc_pdu_sn const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_I (struct llc_pdu_sn const*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 TYPE_1__* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  llc_util_ns_inside_rx_window (scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ) ; 

int llc_conn_ev_rx_i_rsp_fbit_set_1_unexpd_ns(struct sock *sk,
					      struct sk_buff *skb)
{
	const struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	const u8 vr = llc_sk(sk)->vR;
	const u8 ns = LLC_I_GET_NS(pdu);

	return LLC_PDU_IS_RSP(pdu) && LLC_PDU_TYPE_IS_I(pdu) &&
	       LLC_I_PF_IS_1(pdu) && ns != vr &&
	       !llc_util_ns_inside_rx_window(ns, vr, llc_sk(sk)->rw) ? 0 : 1;
}
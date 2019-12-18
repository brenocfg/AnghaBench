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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  tail; int /*<<< orphan*/  len; } ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_hdr {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
#define  RFCOMM_DISC 132 
#define  RFCOMM_DM 131 
#define  RFCOMM_SABM 130 
#define  RFCOMM_UA 129 
#define  RFCOMM_UIH 128 
 scalar_t__ __check_fcs (scalar_t__,int,int) ; 
 int __get_dlci (int /*<<< orphan*/ ) ; 
 int __get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ __test_ea (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_pf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_recv_data (struct rfcomm_session*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct rfcomm_session* rfcomm_recv_disc (struct rfcomm_session*,int) ; 
 struct rfcomm_session* rfcomm_recv_dm (struct rfcomm_session*,int) ; 
 int /*<<< orphan*/  rfcomm_recv_mcc (struct rfcomm_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_recv_sabm (struct rfcomm_session*,int) ; 
 struct rfcomm_session* rfcomm_recv_ua (struct rfcomm_session*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_recv_frame(struct rfcomm_session *s,
						struct sk_buff *skb)
{
	struct rfcomm_hdr *hdr = (void *) skb->data;
	u8 type, dlci, fcs;

	if (!s) {
		/* no session, so free socket data */
		kfree_skb(skb);
		return s;
	}

	dlci = __get_dlci(hdr->addr);
	type = __get_type(hdr->ctrl);

	/* Trim FCS */
	skb->len--; skb->tail--;
	fcs = *(u8 *)skb_tail_pointer(skb);

	if (__check_fcs(skb->data, type, fcs)) {
		BT_ERR("bad checksum in packet");
		kfree_skb(skb);
		return s;
	}

	if (__test_ea(hdr->len))
		skb_pull(skb, 3);
	else
		skb_pull(skb, 4);

	switch (type) {
	case RFCOMM_SABM:
		if (__test_pf(hdr->ctrl))
			rfcomm_recv_sabm(s, dlci);
		break;

	case RFCOMM_DISC:
		if (__test_pf(hdr->ctrl))
			s = rfcomm_recv_disc(s, dlci);
		break;

	case RFCOMM_UA:
		if (__test_pf(hdr->ctrl))
			s = rfcomm_recv_ua(s, dlci);
		break;

	case RFCOMM_DM:
		s = rfcomm_recv_dm(s, dlci);
		break;

	case RFCOMM_UIH:
		if (dlci) {
			rfcomm_recv_data(s, dlci, __test_pf(hdr->ctrl), skb);
			return s;
		}
		rfcomm_recv_mcc(s, skb);
		break;

	default:
		BT_ERR("Unknown packet type 0x%02x", type);
		break;
	}
	kfree_skb(skb);
	return s;
}
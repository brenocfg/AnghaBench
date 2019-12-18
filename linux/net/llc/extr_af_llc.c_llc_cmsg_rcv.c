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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct msghdr {int dummy; } ;
struct llc_sock {int cmsg_flags; TYPE_1__* dev; } ;
struct llc_pktinfo {int /*<<< orphan*/  lpi_mac; int /*<<< orphan*/  lpi_sap; int /*<<< orphan*/  lpi_ifindex; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int LLC_CMSG_PKTINFO ; 
 int /*<<< orphan*/  LLC_OPT_PKTINFO ; 
 int /*<<< orphan*/  SOL_LLC ; 
 int /*<<< orphan*/  llc_pdu_decode_da (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_decode_dsap (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct llc_sock* llc_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct llc_pktinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct llc_pktinfo*) ; 

__attribute__((used)) static void llc_cmsg_rcv(struct msghdr *msg, struct sk_buff *skb)
{
	struct llc_sock *llc = llc_sk(skb->sk);

	if (llc->cmsg_flags & LLC_CMSG_PKTINFO) {
		struct llc_pktinfo info;

		memset(&info, 0, sizeof(info));
		info.lpi_ifindex = llc_sk(skb->sk)->dev->ifindex;
		llc_pdu_decode_dsap(skb, &info.lpi_sap);
		llc_pdu_decode_da(skb, info.lpi_mac);
		put_cmsg(msg, SOL_LLC, LLC_OPT_PKTINFO, sizeof(info), &info);
	}
}
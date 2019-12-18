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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct TYPE_2__ {int /*<<< orphan*/  checksum; } ;
struct pingfakehdr {TYPE_1__ icmph; int /*<<< orphan*/  wcheck; } ;
struct icmphdr {int dummy; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_hdr (struct sk_buff*) ; 
 int ip_push_pending_frames (struct sock*,struct flowi4*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ping_v4_push_pending_frames(struct sock *sk, struct pingfakehdr *pfh,
				       struct flowi4 *fl4)
{
	struct sk_buff *skb = skb_peek(&sk->sk_write_queue);

	if (!skb)
		return 0;
	pfh->wcheck = csum_partial((char *)&pfh->icmph,
		sizeof(struct icmphdr), pfh->wcheck);
	pfh->icmph.checksum = csum_fold(pfh->wcheck);
	memcpy(icmp_hdr(skb), &pfh->icmph, sizeof(struct icmphdr));
	skb->ip_summed = CHECKSUM_NONE;
	return ip_push_pending_frames(sk, fl4);
}
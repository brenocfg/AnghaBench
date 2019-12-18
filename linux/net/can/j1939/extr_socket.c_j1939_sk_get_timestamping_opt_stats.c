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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int tx_acked; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct j1939_session {int /*<<< orphan*/  total_message_size; TYPE_3__ pkt; TYPE_2__ skcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  J1939_NLA_BYTES_ACKED ; 
 scalar_t__ J1939_SIMPLE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_sk_opt_stats_get_size () ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
j1939_sk_get_timestamping_opt_stats(struct j1939_session *session)
{
	struct sk_buff *stats;
	u32 size;

	stats = alloc_skb(j1939_sk_opt_stats_get_size(), GFP_ATOMIC);
	if (!stats)
		return NULL;

	if (session->skcb.addr.type == J1939_SIMPLE)
		size = session->total_message_size;
	else
		size = min(session->pkt.tx_acked * 7,
			   session->total_message_size);

	nla_put_u32(stats, J1939_NLA_BYTES_ACKED, size);

	return stats;
}
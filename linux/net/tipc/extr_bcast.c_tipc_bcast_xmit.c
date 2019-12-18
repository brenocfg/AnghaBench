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
typedef  int u16 ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ELINKCONG ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 struct tipc_link* tipc_bc_sndlink (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_xmit (struct net*,struct sk_buff_head*) ; 
 scalar_t__ tipc_link_bc_peers (struct tipc_link*) ; 
 int tipc_link_xmit (struct tipc_link*,struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static int tipc_bcast_xmit(struct net *net, struct sk_buff_head *pkts,
			   u16 *cong_link_cnt)
{
	struct tipc_link *l = tipc_bc_sndlink(net);
	struct sk_buff_head xmitq;
	int rc = 0;

	__skb_queue_head_init(&xmitq);
	tipc_bcast_lock(net);
	if (tipc_link_bc_peers(l))
		rc = tipc_link_xmit(l, pkts, &xmitq);
	tipc_bcast_unlock(net);
	tipc_bcbase_xmit(net, &xmitq);
	__skb_queue_purge(pkts);
	if (rc == -ELINKCONG) {
		*cong_link_cnt = 1;
		rc = 0;
	}
	return rc;
}
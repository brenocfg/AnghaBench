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
struct sk_buff {int dummy; } ;
struct ip_vs_proto_data {int dummy; } ;
struct ip_vs_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_sctp_state (struct ip_vs_proto_data*,struct ip_vs_conn*,int,struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sctp_state_transition(struct ip_vs_conn *cp, int direction,
		const struct sk_buff *skb, struct ip_vs_proto_data *pd)
{
	spin_lock_bh(&cp->lock);
	set_sctp_state(pd, cp, direction, skb);
	spin_unlock_bh(&cp->lock);
}
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
struct sk_buff_head {int dummy; } ;
struct net {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_nit_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_clone_to_loopback (struct net*,struct sk_buff_head*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tipc_loopback_trace(struct net *net,
				       struct sk_buff_head *pkts)
{
	if (unlikely(dev_nit_active(net->loopback_dev)))
		tipc_clone_to_loopback(net, pkts);
}
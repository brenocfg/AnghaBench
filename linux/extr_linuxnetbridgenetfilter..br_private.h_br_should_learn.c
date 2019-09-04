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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_bridge_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool br_should_learn(struct net_bridge_port *p,
				   struct sk_buff *skb, u16 *vid)
{
	return true;
}
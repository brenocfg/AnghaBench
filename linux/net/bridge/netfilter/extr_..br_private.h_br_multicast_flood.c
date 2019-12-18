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
struct net_bridge_mdb_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void br_multicast_flood(struct net_bridge_mdb_entry *mdst,
				      struct sk_buff *skb,
				      bool local_rcv, bool local_orig)
{
}
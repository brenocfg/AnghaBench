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
struct neighbour {int dummy; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct neighbour* __neigh_lookup_errno (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_neigh_table ; 

__attribute__((used)) static struct neighbour *dn_dst_neigh_lookup(const struct dst_entry *dst,
					     struct sk_buff *skb,
					     const void *daddr)
{
	return __neigh_lookup_errno(&dn_neigh_table, daddr, dst->dev);
}
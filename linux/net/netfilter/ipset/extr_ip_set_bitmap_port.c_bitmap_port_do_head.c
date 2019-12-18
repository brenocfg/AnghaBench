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
struct bitmap_port {int /*<<< orphan*/  last_port; int /*<<< orphan*/  first_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_PORT ; 
 int /*<<< orphan*/  IPSET_ATTR_PORT_TO ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_net16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_port_do_head(struct sk_buff *skb, const struct bitmap_port *map)
{
	return nla_put_net16(skb, IPSET_ATTR_PORT, htons(map->first_port)) ||
	       nla_put_net16(skb, IPSET_ATTR_PORT_TO, htons(map->last_port));
}
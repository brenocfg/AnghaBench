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
struct iphdr {int /*<<< orphan*/  check; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  csum_replace4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clear_hash (struct sk_buff*) ; 
 int /*<<< orphan*/  update_ip_l4_checksum (struct sk_buff*,struct iphdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ip_addr(struct sk_buff *skb, struct iphdr *nh,
			__be32 *addr, __be32 new_addr)
{
	update_ip_l4_checksum(skb, nh, *addr, new_addr);
	csum_replace4(&nh->check, *addr, new_addr);
	skb_clear_hash(skb);
	*addr = new_addr;
}
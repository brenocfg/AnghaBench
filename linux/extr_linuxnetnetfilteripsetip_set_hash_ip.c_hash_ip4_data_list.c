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
struct hash_ip4_elem {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 scalar_t__ nla_put_ipaddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
hash_ip4_data_list(struct sk_buff *skb, const struct hash_ip4_elem *e)
{
	if (nla_put_ipaddr4(skb, IPSET_ATTR_IP, e->ip))
		goto nla_put_failure;
	return false;

nla_put_failure:
	return true;
}
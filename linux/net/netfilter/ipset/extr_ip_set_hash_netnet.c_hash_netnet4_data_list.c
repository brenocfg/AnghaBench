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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct hash_netnet4_elem {int /*<<< orphan*/ * cidr; int /*<<< orphan*/ * ip; scalar_t__ nomatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_CADT_FLAGS ; 
 int /*<<< orphan*/  IPSET_ATTR_CIDR ; 
 int /*<<< orphan*/  IPSET_ATTR_CIDR2 ; 
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  IPSET_ATTR_IP2 ; 
 scalar_t__ IPSET_FLAG_NOMATCH ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nla_put_ipaddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_net32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
hash_netnet4_data_list(struct sk_buff *skb,
		       const struct hash_netnet4_elem *data)
{
	u32 flags = data->nomatch ? IPSET_FLAG_NOMATCH : 0;

	if (nla_put_ipaddr4(skb, IPSET_ATTR_IP, data->ip[0]) ||
	    nla_put_ipaddr4(skb, IPSET_ATTR_IP2, data->ip[1]) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR, data->cidr[0]) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR2, data->cidr[1]) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		goto nla_put_failure;
	return false;

nla_put_failure:
	return true;
}
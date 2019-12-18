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
struct nlattr {int dummy; } ;
struct list_set {size_t size; } ;
struct ip_set {size_t ext_size; size_t ref; size_t elements; int /*<<< orphan*/  dsize; struct list_set* data; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPSET_ATTR_DATA ; 
 int /*<<< orphan*/  IPSET_ATTR_ELEMENTS ; 
 int /*<<< orphan*/  IPSET_ATTR_MEMSIZE ; 
 int /*<<< orphan*/  IPSET_ATTR_REFERENCES ; 
 int /*<<< orphan*/  IPSET_ATTR_SIZE ; 
 int /*<<< orphan*/  htonl (size_t) ; 
 int /*<<< orphan*/  ip_set_put_flags (struct sk_buff*,struct ip_set*) ; 
 size_t list_set_memsize (struct list_set const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_net32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
list_set_head(struct ip_set *set, struct sk_buff *skb)
{
	const struct list_set *map = set->data;
	struct nlattr *nested;
	size_t memsize = list_set_memsize(map, set->dsize) + set->ext_size;

	nested = nla_nest_start(skb, IPSET_ATTR_DATA);
	if (!nested)
		goto nla_put_failure;
	if (nla_put_net32(skb, IPSET_ATTR_SIZE, htonl(map->size)) ||
	    nla_put_net32(skb, IPSET_ATTR_REFERENCES, htonl(set->ref)) ||
	    nla_put_net32(skb, IPSET_ATTR_MEMSIZE, htonl(memsize)) ||
	    nla_put_net32(skb, IPSET_ATTR_ELEMENTS, htonl(set->elements)))
		goto nla_put_failure;
	if (unlikely(ip_set_put_flags(skb, set)))
		goto nla_put_failure;
	nla_nest_end(skb, nested);

	return 0;
nla_put_failure:
	return -EMSGSIZE;
}
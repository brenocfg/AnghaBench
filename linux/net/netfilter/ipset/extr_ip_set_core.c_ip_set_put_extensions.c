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
struct ip_set {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPSET_ATTR_TIMEOUT ; 
 scalar_t__ SET_WITH_COMMENT (struct ip_set const*) ; 
 scalar_t__ SET_WITH_COUNTER (struct ip_set const*) ; 
 scalar_t__ SET_WITH_SKBINFO (struct ip_set const*) ; 
 scalar_t__ SET_WITH_TIMEOUT (struct ip_set const*) ; 
 int /*<<< orphan*/  ext_comment (void const*,struct ip_set const*) ; 
 int /*<<< orphan*/  ext_counter (void const*,struct ip_set const*) ; 
 int /*<<< orphan*/  ext_skbinfo (void const*,struct ip_set const*) ; 
 unsigned long* ext_timeout (void const*,struct ip_set const*) ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 
 scalar_t__ ip_set_put_comment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_set_put_counter (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_set_put_skbinfo (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned long ip_set_timeout_get (unsigned long*) ; 
 scalar_t__ nla_put_net32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ip_set_put_extensions(struct sk_buff *skb, const struct ip_set *set,
		      const void *e, bool active)
{
	if (SET_WITH_TIMEOUT(set)) {
		unsigned long *timeout = ext_timeout(e, set);

		if (nla_put_net32(skb, IPSET_ATTR_TIMEOUT,
			htonl(active ? ip_set_timeout_get(timeout)
				: *timeout)))
			return -EMSGSIZE;
	}
	if (SET_WITH_COUNTER(set) &&
	    ip_set_put_counter(skb, ext_counter(e, set)))
		return -EMSGSIZE;
	if (SET_WITH_COMMENT(set) &&
	    ip_set_put_comment(skb, ext_comment(e, set)))
		return -EMSGSIZE;
	if (SET_WITH_SKBINFO(set) &&
	    ip_set_put_skbinfo(skb, ext_skbinfo(e, set)))
		return -EMSGSIZE;
	return 0;
}
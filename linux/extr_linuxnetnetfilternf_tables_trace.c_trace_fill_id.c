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
struct sk_buff {int /*<<< orphan*/  skb_iif; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_TRACE_ID ; 
 int /*<<< orphan*/  hash32_ptr (struct sk_buff*) ; 
 scalar_t__ jhash_2words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_get_hash (struct sk_buff*) ; 

__attribute__((used)) static int trace_fill_id(struct sk_buff *nlskb, struct sk_buff *skb)
{
	__be32 id;

	/* using skb address as ID results in a limited number of
	 * values (and quick reuse).
	 *
	 * So we attempt to use as many skb members that will not
	 * change while skb is with netfilter.
	 */
	id = (__be32)jhash_2words(hash32_ptr(skb), skb_get_hash(skb),
				  skb->skb_iif);

	return nla_put_be32(nlskb, NFTA_TRACE_ID, id);
}
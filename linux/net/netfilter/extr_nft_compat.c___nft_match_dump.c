#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_match {int /*<<< orphan*/  usersize; int /*<<< orphan*/  matchsize; int /*<<< orphan*/  revision; int /*<<< orphan*/  name; } ;
struct sk_buff {int dummy; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct TYPE_2__ {struct xt_match* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_MATCH_INFO ; 
 int /*<<< orphan*/  NFTA_MATCH_NAME ; 
 int /*<<< orphan*/  NFTA_MATCH_REV ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_extension_dump_info (struct sk_buff*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nft_match_dump(struct sk_buff *skb, const struct nft_expr *expr,
			    void *info)
{
	struct xt_match *match = expr->ops->data;

	if (nla_put_string(skb, NFTA_MATCH_NAME, match->name) ||
	    nla_put_be32(skb, NFTA_MATCH_REV, htonl(match->revision)) ||
	    nft_extension_dump_info(skb, NFTA_MATCH_INFO, info,
				    match->matchsize, match->usersize))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nft_object {TYPE_2__* ops; int /*<<< orphan*/  name; } ;
struct nft_expr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_OBJREF_IMM_NAME ; 
 int /*<<< orphan*/  NFTA_OBJREF_IMM_TYPE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct nft_object* nft_objref_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_objref_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_object *obj = nft_objref_priv(expr);

	if (nla_put_string(skb, NFTA_OBJREF_IMM_NAME, obj->name) ||
	    nla_put_be32(skb, NFTA_OBJREF_IMM_TYPE,
			 htonl(obj->ops->type->type)))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}
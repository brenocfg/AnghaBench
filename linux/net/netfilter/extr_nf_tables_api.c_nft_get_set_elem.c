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
typedef  int /*<<< orphan*/  uint32_t ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
struct nft_set_elem {void* priv; TYPE_1__ key; } ;
struct nft_set {scalar_t__ klen; TYPE_2__* ops; } ;
struct nft_data_desc {scalar_t__ type; scalar_t__ len; } ;
struct nft_ctx {int /*<<< orphan*/  portid; int /*<<< orphan*/  net; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {void* (* get ) (int /*<<< orphan*/ ,struct nft_set*,struct nft_set_elem*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 size_t NFTA_SET_ELEM_FLAGS ; 
 size_t NFTA_SET_ELEM_KEY ; 
 int /*<<< orphan*/  NFTA_SET_ELEM_MAX ; 
 scalar_t__ NFT_DATA_VALUE ; 
 int /*<<< orphan*/  NFT_MSG_NEWSETELEM ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_setelem_info (struct sk_buff*,struct nft_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nft_set*,struct nft_set_elem*) ; 
 int nfnetlink_unicast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_data_init (struct nft_ctx*,int /*<<< orphan*/ *,int,struct nft_data_desc*,struct nlattr*) ; 
 int /*<<< orphan*/  nft_set_elem_policy ; 
 int nft_setelem_parse_flags (struct nft_set*,struct nlattr*,int /*<<< orphan*/ *) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stub1 (int /*<<< orphan*/ ,struct nft_set*,struct nft_set_elem*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_get_set_elem(struct nft_ctx *ctx, struct nft_set *set,
			    const struct nlattr *attr)
{
	struct nlattr *nla[NFTA_SET_ELEM_MAX + 1];
	struct nft_data_desc desc;
	struct nft_set_elem elem;
	struct sk_buff *skb;
	uint32_t flags = 0;
	void *priv;
	int err;

	err = nla_parse_nested_deprecated(nla, NFTA_SET_ELEM_MAX, attr,
					  nft_set_elem_policy, NULL);
	if (err < 0)
		return err;

	if (!nla[NFTA_SET_ELEM_KEY])
		return -EINVAL;

	err = nft_setelem_parse_flags(set, nla[NFTA_SET_ELEM_FLAGS], &flags);
	if (err < 0)
		return err;

	err = nft_data_init(ctx, &elem.key.val, sizeof(elem.key), &desc,
			    nla[NFTA_SET_ELEM_KEY]);
	if (err < 0)
		return err;

	err = -EINVAL;
	if (desc.type != NFT_DATA_VALUE || desc.len != set->klen)
		return err;

	priv = set->ops->get(ctx->net, set, &elem, flags);
	if (IS_ERR(priv))
		return PTR_ERR(priv);

	elem.priv = priv;

	err = -ENOMEM;
	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	if (skb == NULL)
		goto err1;

	err = nf_tables_fill_setelem_info(skb, ctx, ctx->seq, ctx->portid,
					  NFT_MSG_NEWSETELEM, 0, set, &elem);
	if (err < 0)
		goto err2;

	err = nfnetlink_unicast(skb, ctx->net, ctx->portid, MSG_DONTWAIT);
	/* This avoids a loop in nfnetlink. */
	if (err < 0)
		goto err1;

	return 0;
err2:
	kfree_skb(skb);
err1:
	/* this avoids a loop in nfnetlink. */
	return err == -EAGAIN ? -ENOBUFS : err;
}
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
struct nlattr {int dummy; } ;
struct nft_object {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_ct_expect_obj {void* size; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dport; void* l4proto; int /*<<< orphan*/  l3num; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_CT_EXPECT_DPORT ; 
 size_t NFTA_CT_EXPECT_L3PROTO ; 
 size_t NFTA_CT_EXPECT_L4PROTO ; 
 size_t NFTA_CT_EXPECT_SIZE ; 
 size_t NFTA_CT_EXPECT_TIMEOUT ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_ct_expect_obj* nft_obj_data (struct nft_object*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr const* const) ; 
 void* nla_get_u8 (struct nlattr const* const) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ct_expect_obj_init(const struct nft_ctx *ctx,
				  const struct nlattr * const tb[],
				  struct nft_object *obj)
{
	struct nft_ct_expect_obj *priv = nft_obj_data(obj);

	if (!tb[NFTA_CT_EXPECT_L4PROTO] ||
	    !tb[NFTA_CT_EXPECT_DPORT] ||
	    !tb[NFTA_CT_EXPECT_TIMEOUT] ||
	    !tb[NFTA_CT_EXPECT_SIZE])
		return -EINVAL;

	priv->l3num = ctx->family;
	if (tb[NFTA_CT_EXPECT_L3PROTO])
		priv->l3num = ntohs(nla_get_be16(tb[NFTA_CT_EXPECT_L3PROTO]));

	priv->l4proto = nla_get_u8(tb[NFTA_CT_EXPECT_L4PROTO]);
	priv->dport = nla_get_be16(tb[NFTA_CT_EXPECT_DPORT]);
	priv->timeout = nla_get_u32(tb[NFTA_CT_EXPECT_TIMEOUT]);
	priv->size = nla_get_u8(tb[NFTA_CT_EXPECT_SIZE]);

	return nf_ct_netns_get(ctx->net, ctx->family);
}
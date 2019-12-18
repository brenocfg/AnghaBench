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
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_connlimit {int limit; int invert; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NFTA_CONNLIMIT_COUNT ; 
 size_t NFTA_CONNLIMIT_FLAGS ; 
 int NFT_CONNLIMIT_F_INV ; 
 int /*<<< orphan*/  nf_conncount_list_init (int /*<<< orphan*/ *) ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_connlimit_do_init(const struct nft_ctx *ctx,
				 const struct nlattr * const tb[],
				 struct nft_connlimit *priv)
{
	bool invert = false;
	u32 flags, limit;

	if (!tb[NFTA_CONNLIMIT_COUNT])
		return -EINVAL;

	limit = ntohl(nla_get_be32(tb[NFTA_CONNLIMIT_COUNT]));

	if (tb[NFTA_CONNLIMIT_FLAGS]) {
		flags = ntohl(nla_get_be32(tb[NFTA_CONNLIMIT_FLAGS]));
		if (flags & ~NFT_CONNLIMIT_F_INV)
			return -EOPNOTSUPP;
		if (flags & NFT_CONNLIMIT_F_INV)
			invert = true;
	}

	nf_conncount_list_init(&priv->list);
	priv->limit	= limit;
	priv->invert	= invert;

	return nf_ct_netns_get(ctx->net, ctx->family);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct nft_offload_reg {int offset; size_t key; int /*<<< orphan*/  base_offset; int /*<<< orphan*/  mask; int /*<<< orphan*/  len; } ;
struct nft_offload_ctx {struct nft_offload_reg* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * offset; int /*<<< orphan*/  used_keys; } ;
struct TYPE_4__ {TYPE_1__ dissector; int /*<<< orphan*/  key; int /*<<< orphan*/  mask; } ;
struct nft_flow_rule {TYPE_2__ match; } ;
struct nft_cmp_expr {size_t sreg; scalar_t__ op; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int EOPNOTSUPP ; 
 scalar_t__ NFT_CMP_EQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_offload_update_dependency (struct nft_offload_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nft_cmp_offload(struct nft_offload_ctx *ctx,
			     struct nft_flow_rule *flow,
			     const struct nft_cmp_expr *priv)
{
	struct nft_offload_reg *reg = &ctx->regs[priv->sreg];
	u8 *mask = (u8 *)&flow->match.mask;
	u8 *key = (u8 *)&flow->match.key;

	if (priv->op != NFT_CMP_EQ || reg->len != priv->len)
		return -EOPNOTSUPP;

	memcpy(key + reg->offset, &priv->data, priv->len);
	memcpy(mask + reg->offset, &reg->mask, priv->len);

	flow->match.dissector.used_keys |= BIT(reg->key);
	flow->match.dissector.offset[reg->key] = reg->base_offset;

	nft_offload_update_dependency(ctx, &priv->data, priv->len);

	return 0;
}
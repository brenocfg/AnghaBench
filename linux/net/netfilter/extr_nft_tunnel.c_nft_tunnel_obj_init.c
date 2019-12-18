#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  u; } ;
struct nft_tunnel_obj {struct metadata_dst* md; TYPE_3__ opts; } ;
struct nft_object {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst_cache; } ;
struct TYPE_7__ {TYPE_4__ tun_info; } ;
struct metadata_dst {TYPE_2__ u; } ;
struct TYPE_6__ {int tun_flags; void* ttl; void* tos; void* tp_dst; void* tp_src; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {TYPE_1__ key; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP_TUNNEL_INFO_TX ; 
 int /*<<< orphan*/  METADATA_IP_TUNNEL ; 
 size_t NFTA_TUNNEL_KEY_DPORT ; 
 size_t NFTA_TUNNEL_KEY_FLAGS ; 
 size_t NFTA_TUNNEL_KEY_ID ; 
 size_t NFTA_TUNNEL_KEY_IP ; 
 size_t NFTA_TUNNEL_KEY_IP6 ; 
 size_t NFTA_TUNNEL_KEY_OPTS ; 
 size_t NFTA_TUNNEL_KEY_SPORT ; 
 size_t NFTA_TUNNEL_KEY_TOS ; 
 size_t NFTA_TUNNEL_KEY_TTL ; 
 int NFT_TUNNEL_F_DONT_FRAGMENT ; 
 int NFT_TUNNEL_F_MASK ; 
 int NFT_TUNNEL_F_SEQ_NUMBER ; 
 int NFT_TUNNEL_F_ZERO_CSUM_TX ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int TUNNEL_KEY ; 
 int TUNNEL_NOCACHE ; 
 int TUNNEL_SEQ ; 
 void* U8_MAX ; 
 int dst_cache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_info_opts_set (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key32_to_tunnel_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct ip_tunnel_info*,int) ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_info*,int /*<<< orphan*/ ,int) ; 
 struct metadata_dst* metadata_dst_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_dst_free (struct metadata_dst*) ; 
 struct nft_tunnel_obj* nft_obj_data (struct nft_object*) ; 
 int nft_tunnel_obj_ip6_init (struct nft_ctx const*,struct nlattr const* const,struct ip_tunnel_info*) ; 
 int nft_tunnel_obj_ip_init (struct nft_ctx const*,struct nlattr const* const,struct ip_tunnel_info*) ; 
 int nft_tunnel_obj_opts_init (struct nft_ctx const*,struct nlattr const* const,struct ip_tunnel_info*,TYPE_3__*) ; 
 void* nla_get_be16 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* nla_get_u8 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_obj_init(const struct nft_ctx *ctx,
			       const struct nlattr * const tb[],
			       struct nft_object *obj)
{
	struct nft_tunnel_obj *priv = nft_obj_data(obj);
	struct ip_tunnel_info info;
	struct metadata_dst *md;
	int err;

	if (!tb[NFTA_TUNNEL_KEY_ID])
		return -EINVAL;

	memset(&info, 0, sizeof(info));
	info.mode		= IP_TUNNEL_INFO_TX;
	info.key.tun_id		= key32_to_tunnel_id(nla_get_be32(tb[NFTA_TUNNEL_KEY_ID]));
	info.key.tun_flags	= TUNNEL_KEY | TUNNEL_CSUM | TUNNEL_NOCACHE;

	if (tb[NFTA_TUNNEL_KEY_IP]) {
		err = nft_tunnel_obj_ip_init(ctx, tb[NFTA_TUNNEL_KEY_IP], &info);
		if (err < 0)
			return err;
	} else if (tb[NFTA_TUNNEL_KEY_IP6]) {
		err = nft_tunnel_obj_ip6_init(ctx, tb[NFTA_TUNNEL_KEY_IP6], &info);
		if (err < 0)
			return err;
	} else {
		return -EINVAL;
	}

	if (tb[NFTA_TUNNEL_KEY_SPORT]) {
		info.key.tp_src = nla_get_be16(tb[NFTA_TUNNEL_KEY_SPORT]);
	}
	if (tb[NFTA_TUNNEL_KEY_DPORT]) {
		info.key.tp_dst = nla_get_be16(tb[NFTA_TUNNEL_KEY_DPORT]);
	}

	if (tb[NFTA_TUNNEL_KEY_FLAGS]) {
		u32 tun_flags;

		tun_flags = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_FLAGS]));
		if (tun_flags & ~NFT_TUNNEL_F_MASK)
			return -EOPNOTSUPP;

		if (tun_flags & NFT_TUNNEL_F_ZERO_CSUM_TX)
			info.key.tun_flags &= ~TUNNEL_CSUM;
		if (tun_flags & NFT_TUNNEL_F_DONT_FRAGMENT)
			info.key.tun_flags |= TUNNEL_DONT_FRAGMENT;
		if (tun_flags & NFT_TUNNEL_F_SEQ_NUMBER)
			info.key.tun_flags |= TUNNEL_SEQ;
	}
	if (tb[NFTA_TUNNEL_KEY_TOS])
		info.key.tos = nla_get_u8(tb[NFTA_TUNNEL_KEY_TOS]);
	if (tb[NFTA_TUNNEL_KEY_TTL])
		info.key.ttl = nla_get_u8(tb[NFTA_TUNNEL_KEY_TTL]);
	else
		info.key.ttl = U8_MAX;

	if (tb[NFTA_TUNNEL_KEY_OPTS]) {
		err = nft_tunnel_obj_opts_init(ctx, tb[NFTA_TUNNEL_KEY_OPTS],
					       &info, &priv->opts);
		if (err < 0)
			return err;
	}

	md = metadata_dst_alloc(priv->opts.len, METADATA_IP_TUNNEL, GFP_KERNEL);
	if (!md)
		return -ENOMEM;

	memcpy(&md->u.tun_info, &info, sizeof(info));
#ifdef CONFIG_DST_CACHE
	err = dst_cache_init(&md->u.tun_info.dst_cache, GFP_KERNEL);
	if (err < 0) {
		metadata_dst_free(md);
		return err;
	}
#endif
	ip_tunnel_info_opts_set(&md->u.tun_info, &priv->opts.u, priv->opts.len,
				priv->opts.flags);
	priv->md = md;

	return 0;
}
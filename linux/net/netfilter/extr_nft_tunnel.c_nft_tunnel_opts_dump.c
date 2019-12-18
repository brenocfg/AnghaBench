#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dir; } ;
struct TYPE_7__ {TYPE_5__ md2; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int version; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  gbp; } ;
struct TYPE_9__ {TYPE_3__ erspan; TYPE_1__ vxlan; } ;
struct nft_tunnel_opts {int flags; TYPE_4__ u; } ;
struct nft_tunnel_obj {struct nft_tunnel_opts opts; } ;

/* Variables and functions */
#define  ERSPAN_VERSION 129 
#define  ERSPAN_VERSION2 128 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_ERSPAN_V2_DIR ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_ERSPAN_V2_HWID ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_OPTS ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_VXLAN_GBP ; 
 int TUNNEL_ERSPAN_OPT ; 
 int TUNNEL_VXLAN_OPT ; 
 int /*<<< orphan*/  get_hwid (TYPE_5__*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_opts_dump(struct sk_buff *skb,
				struct nft_tunnel_obj *priv)
{
	struct nft_tunnel_opts *opts = &priv->opts;
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_OPTS);
	if (!nest)
		return -1;

	if (opts->flags & TUNNEL_VXLAN_OPT) {
		if (nla_put_be32(skb, NFTA_TUNNEL_KEY_VXLAN_GBP,
				 htonl(opts->u.vxlan.gbp)))
			return -1;
	} else if (opts->flags & TUNNEL_ERSPAN_OPT) {
		switch (opts->u.erspan.version) {
		case ERSPAN_VERSION:
			if (nla_put_be32(skb, NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX,
					 opts->u.erspan.u.index))
				return -1;
			break;
		case ERSPAN_VERSION2:
			if (nla_put_u8(skb, NFTA_TUNNEL_KEY_ERSPAN_V2_HWID,
				       get_hwid(&opts->u.erspan.u.md2)) ||
			    nla_put_u8(skb, NFTA_TUNNEL_KEY_ERSPAN_V2_DIR,
				       opts->u.erspan.u.md2.dir))
				return -1;
			break;
		}
	}
	nla_nest_end(skb, nest);

	return 0;
}
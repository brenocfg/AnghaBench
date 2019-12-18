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
struct vxlan_metadata {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gbp; } ;
struct TYPE_4__ {TYPE_1__ vxlan; } ;
struct nft_tunnel_opts {int len; int /*<<< orphan*/  flags; TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_TUNNEL_KEY_VXLAN_GBP ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_VXLAN_MAX ; 
 int /*<<< orphan*/  TUNNEL_VXLAN_OPT ; 
 int /*<<< orphan*/  nft_tunnel_opts_vxlan_policy ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_obj_vxlan_init(const struct nlattr *attr,
				     struct nft_tunnel_opts *opts)
{
	struct nlattr *tb[NFTA_TUNNEL_KEY_VXLAN_MAX + 1];
	int err;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_VXLAN_MAX, attr,
					  nft_tunnel_opts_vxlan_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[NFTA_TUNNEL_KEY_VXLAN_GBP])
		return -EINVAL;

	opts->u.vxlan.gbp = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_VXLAN_GBP]));

	opts->len	= sizeof(struct vxlan_metadata);
	opts->flags	= TUNNEL_VXLAN_OPT;

	return 0;
}
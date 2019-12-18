#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {TYPE_1__ ipv6; } ;
struct TYPE_6__ {int /*<<< orphan*/  label; TYPE_2__ u; } ;
struct ip_tunnel_info {int /*<<< orphan*/  mode; TYPE_3__ key; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IP_TUNNEL_INFO_IPV6 ; 
 size_t NFTA_TUNNEL_KEY_IP6_DST ; 
 size_t NFTA_TUNNEL_KEY_IP6_FLOWLABEL ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_IP6_MAX ; 
 size_t NFTA_TUNNEL_KEY_IP6_SRC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nft_tunnel_ip6_policy ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nft_tunnel_obj_ip6_init(const struct nft_ctx *ctx,
				   const struct nlattr *attr,
				   struct ip_tunnel_info *info)
{
	struct nlattr *tb[NFTA_TUNNEL_KEY_IP6_MAX + 1];
	int err;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_IP6_MAX, attr,
					  nft_tunnel_ip6_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[NFTA_TUNNEL_KEY_IP6_DST])
		return -EINVAL;

	if (tb[NFTA_TUNNEL_KEY_IP6_SRC]) {
		memcpy(&info->key.u.ipv6.src,
		       nla_data(tb[NFTA_TUNNEL_KEY_IP6_SRC]),
		       sizeof(struct in6_addr));
	}
	if (tb[NFTA_TUNNEL_KEY_IP6_DST]) {
		memcpy(&info->key.u.ipv6.dst,
		       nla_data(tb[NFTA_TUNNEL_KEY_IP6_DST]),
		       sizeof(struct in6_addr));
	}
	if (tb[NFTA_TUNNEL_KEY_IP6_FLOWLABEL])
		info->key.label = nla_get_be32(tb[NFTA_TUNNEL_KEY_IP6_FLOWLABEL]);

	info->mode |= IP_TUNNEL_INFO_IPV6;

	return 0;
}
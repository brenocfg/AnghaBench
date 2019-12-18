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
struct netlink_ext_ack {int dummy; } ;
struct lwtunnel_state {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {void* src; void* dst; } ;
struct TYPE_5__ {TYPE_1__ ipv6; } ;
struct TYPE_6__ {int /*<<< orphan*/  tun_flags; void* tos; void* ttl; TYPE_2__ u; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; scalar_t__ options_len; TYPE_3__ key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IP_TUNNEL_INFO_IPV6 ; 
 int IP_TUNNEL_INFO_TX ; 
 int /*<<< orphan*/  LWTUNNEL_ENCAP_IP6 ; 
 size_t LWTUNNEL_IP6_DST ; 
 size_t LWTUNNEL_IP6_FLAGS ; 
 size_t LWTUNNEL_IP6_HOPLIMIT ; 
 size_t LWTUNNEL_IP6_ID ; 
 int /*<<< orphan*/  LWTUNNEL_IP6_MAX ; 
 size_t LWTUNNEL_IP6_SRC ; 
 size_t LWTUNNEL_IP6_TC ; 
 int /*<<< orphan*/  ip6_tun_policy ; 
 struct ip_tunnel_info* lwt_tun_info (struct lwtunnel_state*) ; 
 struct lwtunnel_state* lwtunnel_state_alloc (int) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be64 (struct nlattr*) ; 
 void* nla_get_in6_addr (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int ip6_tun_build_state(struct nlattr *attr,
			       unsigned int family, const void *cfg,
			       struct lwtunnel_state **ts,
			       struct netlink_ext_ack *extack)
{
	struct ip_tunnel_info *tun_info;
	struct lwtunnel_state *new_state;
	struct nlattr *tb[LWTUNNEL_IP6_MAX + 1];
	int err;

	err = nla_parse_nested_deprecated(tb, LWTUNNEL_IP6_MAX, attr,
					  ip6_tun_policy, extack);
	if (err < 0)
		return err;

	new_state = lwtunnel_state_alloc(sizeof(*tun_info));
	if (!new_state)
		return -ENOMEM;

	new_state->type = LWTUNNEL_ENCAP_IP6;

	tun_info = lwt_tun_info(new_state);

	if (tb[LWTUNNEL_IP6_ID])
		tun_info->key.tun_id = nla_get_be64(tb[LWTUNNEL_IP6_ID]);

	if (tb[LWTUNNEL_IP6_DST])
		tun_info->key.u.ipv6.dst = nla_get_in6_addr(tb[LWTUNNEL_IP6_DST]);

	if (tb[LWTUNNEL_IP6_SRC])
		tun_info->key.u.ipv6.src = nla_get_in6_addr(tb[LWTUNNEL_IP6_SRC]);

	if (tb[LWTUNNEL_IP6_HOPLIMIT])
		tun_info->key.ttl = nla_get_u8(tb[LWTUNNEL_IP6_HOPLIMIT]);

	if (tb[LWTUNNEL_IP6_TC])
		tun_info->key.tos = nla_get_u8(tb[LWTUNNEL_IP6_TC]);

	if (tb[LWTUNNEL_IP6_FLAGS])
		tun_info->key.tun_flags = nla_get_be16(tb[LWTUNNEL_IP6_FLAGS]);

	tun_info->mode = IP_TUNNEL_INFO_TX | IP_TUNNEL_INFO_IPV6;
	tun_info->options_len = 0;

	*ts = new_state;

	return 0;
}
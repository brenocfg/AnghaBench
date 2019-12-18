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
struct ovs_tunnel_info {TYPE_1__* tun_dst; } ;
struct nlattr {int dummy; } ;
struct ip_tunnel_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  options_len; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {struct ip_tunnel_info tun_info; } ;
struct TYPE_3__ {TYPE_2__ u; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_SET ; 
#define  OVS_KEY_ATTR_TUNNEL_INFO 128 
 int ip_tun_to_nlattr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  ip_tunnel_info_opts (struct ip_tunnel_info*) ; 
 void* nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr const*) ; 
 int nla_type (struct nlattr const*) ; 

__attribute__((used)) static int set_action_to_attr(const struct nlattr *a, struct sk_buff *skb)
{
	const struct nlattr *ovs_key = nla_data(a);
	int key_type = nla_type(ovs_key);
	struct nlattr *start;
	int err;

	switch (key_type) {
	case OVS_KEY_ATTR_TUNNEL_INFO: {
		struct ovs_tunnel_info *ovs_tun = nla_data(ovs_key);
		struct ip_tunnel_info *tun_info = &ovs_tun->tun_dst->u.tun_info;

		start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_SET);
		if (!start)
			return -EMSGSIZE;

		err =  ip_tun_to_nlattr(skb, &tun_info->key,
					ip_tunnel_info_opts(tun_info),
					tun_info->options_len,
					ip_tunnel_info_af(tun_info), tun_info->mode);
		if (err)
			return err;
		nla_nest_end(skb, start);
		break;
	}
	default:
		if (nla_put(skb, OVS_ACTION_ATTR_SET, nla_len(a), ovs_key))
			return -EMSGSIZE;
		break;
	}

	return 0;
}
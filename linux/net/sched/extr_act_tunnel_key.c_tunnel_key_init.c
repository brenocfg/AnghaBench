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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_tunnel_key_params {int tcft_action; struct metadata_dst* tcft_enc_metadata; } ;
struct tcf_tunnel_key {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; } ;
struct tcf_proto {int dummy; } ;
struct tcf_chain {int dummy; } ;
struct tc_tunnel_key {int t_action; int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  dst_cache; } ;
struct TYPE_3__ {TYPE_2__ tun_info; } ;
struct metadata_dst {int /*<<< orphan*/  dst; TYPE_1__ u; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP_TUNNEL_INFO_TX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
#define  TCA_TUNNEL_KEY_ACT_RELEASE 129 
#define  TCA_TUNNEL_KEY_ACT_SET 128 
 size_t TCA_TUNNEL_KEY_ENC_DST_PORT ; 
 size_t TCA_TUNNEL_KEY_ENC_IPV4_DST ; 
 size_t TCA_TUNNEL_KEY_ENC_IPV4_SRC ; 
 size_t TCA_TUNNEL_KEY_ENC_IPV6_DST ; 
 size_t TCA_TUNNEL_KEY_ENC_IPV6_SRC ; 
 size_t TCA_TUNNEL_KEY_ENC_KEY_ID ; 
 size_t TCA_TUNNEL_KEY_ENC_OPTS ; 
 size_t TCA_TUNNEL_KEY_ENC_TOS ; 
 size_t TCA_TUNNEL_KEY_ENC_TTL ; 
 int /*<<< orphan*/  TCA_TUNNEL_KEY_MAX ; 
 size_t TCA_TUNNEL_KEY_NO_CSUM ; 
 size_t TCA_TUNNEL_KEY_PARMS ; 
 int /*<<< orphan*/  TUNNEL_CSUM ; 
 int /*<<< orphan*/  TUNNEL_KEY ; 
 struct metadata_dst* __ip_tun_set_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct metadata_dst* __ipv6_tun_set_dst (struct in6_addr*,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  act_tunnel_key_ops ; 
 int dst_cache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key32_to_tunnel_id (int /*<<< orphan*/ ) ; 
 struct tcf_tunnel_key_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_tunnel_key* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 struct in6_addr nla_get_in6_addr (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_in_addr (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_tunnel_key_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_tunnel_key* to_tunnel_key (struct tc_action*) ; 
 int tunnel_key_get_opts_len (struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tunnel_key_net_id ; 
 int tunnel_key_opts_set (struct nlattr*,TYPE_2__*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tunnel_key_policy ; 
 int /*<<< orphan*/  tunnel_key_release_params (struct tcf_tunnel_key_params*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tunnel_key_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a,
			   int ovr, int bind, bool rtnl_held,
			   struct tcf_proto *tp,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, tunnel_key_net_id);
	struct nlattr *tb[TCA_TUNNEL_KEY_MAX + 1];
	struct tcf_tunnel_key_params *params_new;
	struct metadata_dst *metadata = NULL;
	struct tcf_chain *goto_ch = NULL;
	struct tc_tunnel_key *parm;
	struct tcf_tunnel_key *t;
	bool exists = false;
	__be16 dst_port = 0;
	__be64 key_id = 0;
	int opts_len = 0;
	__be16 flags = 0;
	u8 tos, ttl;
	int ret = 0;
	u32 index;
	int err;

	if (!nla) {
		NL_SET_ERR_MSG(extack, "Tunnel requires attributes to be passed");
		return -EINVAL;
	}

	err = nla_parse_nested_deprecated(tb, TCA_TUNNEL_KEY_MAX, nla,
					  tunnel_key_policy, extack);
	if (err < 0) {
		NL_SET_ERR_MSG(extack, "Failed to parse nested tunnel key attributes");
		return err;
	}

	if (!tb[TCA_TUNNEL_KEY_PARMS]) {
		NL_SET_ERR_MSG(extack, "Missing tunnel key parameters");
		return -EINVAL;
	}

	parm = nla_data(tb[TCA_TUNNEL_KEY_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	switch (parm->t_action) {
	case TCA_TUNNEL_KEY_ACT_RELEASE:
		break;
	case TCA_TUNNEL_KEY_ACT_SET:
		if (tb[TCA_TUNNEL_KEY_ENC_KEY_ID]) {
			__be32 key32;

			key32 = nla_get_be32(tb[TCA_TUNNEL_KEY_ENC_KEY_ID]);
			key_id = key32_to_tunnel_id(key32);
			flags = TUNNEL_KEY;
		}

		flags |= TUNNEL_CSUM;
		if (tb[TCA_TUNNEL_KEY_NO_CSUM] &&
		    nla_get_u8(tb[TCA_TUNNEL_KEY_NO_CSUM]))
			flags &= ~TUNNEL_CSUM;

		if (tb[TCA_TUNNEL_KEY_ENC_DST_PORT])
			dst_port = nla_get_be16(tb[TCA_TUNNEL_KEY_ENC_DST_PORT]);

		if (tb[TCA_TUNNEL_KEY_ENC_OPTS]) {
			opts_len = tunnel_key_get_opts_len(tb[TCA_TUNNEL_KEY_ENC_OPTS],
							   extack);
			if (opts_len < 0) {
				ret = opts_len;
				goto err_out;
			}
		}

		tos = 0;
		if (tb[TCA_TUNNEL_KEY_ENC_TOS])
			tos = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_TOS]);
		ttl = 0;
		if (tb[TCA_TUNNEL_KEY_ENC_TTL])
			ttl = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_TTL]);

		if (tb[TCA_TUNNEL_KEY_ENC_IPV4_SRC] &&
		    tb[TCA_TUNNEL_KEY_ENC_IPV4_DST]) {
			__be32 saddr;
			__be32 daddr;

			saddr = nla_get_in_addr(tb[TCA_TUNNEL_KEY_ENC_IPV4_SRC]);
			daddr = nla_get_in_addr(tb[TCA_TUNNEL_KEY_ENC_IPV4_DST]);

			metadata = __ip_tun_set_dst(saddr, daddr, tos, ttl,
						    dst_port, flags,
						    key_id, opts_len);
		} else if (tb[TCA_TUNNEL_KEY_ENC_IPV6_SRC] &&
			   tb[TCA_TUNNEL_KEY_ENC_IPV6_DST]) {
			struct in6_addr saddr;
			struct in6_addr daddr;

			saddr = nla_get_in6_addr(tb[TCA_TUNNEL_KEY_ENC_IPV6_SRC]);
			daddr = nla_get_in6_addr(tb[TCA_TUNNEL_KEY_ENC_IPV6_DST]);

			metadata = __ipv6_tun_set_dst(&saddr, &daddr, tos, ttl, dst_port,
						      0, flags,
						      key_id, 0);
		} else {
			NL_SET_ERR_MSG(extack, "Missing either ipv4 or ipv6 src and dst");
			ret = -EINVAL;
			goto err_out;
		}

		if (!metadata) {
			NL_SET_ERR_MSG(extack, "Cannot allocate tunnel metadata dst");
			ret = -ENOMEM;
			goto err_out;
		}

#ifdef CONFIG_DST_CACHE
		ret = dst_cache_init(&metadata->u.tun_info.dst_cache, GFP_KERNEL);
		if (ret)
			goto release_tun_meta;
#endif

		if (opts_len) {
			ret = tunnel_key_opts_set(tb[TCA_TUNNEL_KEY_ENC_OPTS],
						  &metadata->u.tun_info,
						  opts_len, extack);
			if (ret < 0)
				goto release_tun_meta;
		}

		metadata->u.tun_info.mode |= IP_TUNNEL_INFO_TX;
		break;
	default:
		NL_SET_ERR_MSG(extack, "Unknown tunnel key action");
		ret = -EINVAL;
		goto err_out;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_tunnel_key_ops, bind, true);
		if (ret) {
			NL_SET_ERR_MSG(extack, "Cannot create TC IDR");
			goto release_tun_meta;
		}

		ret = ACT_P_CREATED;
	} else if (!ovr) {
		NL_SET_ERR_MSG(extack, "TC IDR already exists");
		ret = -EEXIST;
		goto release_tun_meta;
	}

	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0) {
		ret = err;
		exists = true;
		goto release_tun_meta;
	}
	t = to_tunnel_key(*a);

	params_new = kzalloc(sizeof(*params_new), GFP_KERNEL);
	if (unlikely(!params_new)) {
		NL_SET_ERR_MSG(extack, "Cannot allocate tunnel key parameters");
		ret = -ENOMEM;
		exists = true;
		goto put_chain;
	}
	params_new->tcft_action = parm->t_action;
	params_new->tcft_enc_metadata = metadata;

	spin_lock_bh(&t->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	rcu_swap_protected(t->params, params_new,
			   lockdep_is_held(&t->tcf_lock));
	spin_unlock_bh(&t->tcf_lock);
	tunnel_key_release_params(params_new);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);

	return ret;

put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

release_tun_meta:
	if (metadata)
		dst_release(&metadata->dst);

err_out:
	if (exists)
		tcf_idr_release(*a, bind);
	else
		tcf_idr_cleanup(tn, index);
	return ret;
}
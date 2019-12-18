#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct l2tp_tunnel {int version; } ;
struct l2tp_session_cfg {size_t pw_type; scalar_t__ l2specific_type; int cookie_len; int peer_cookie_len; int /*<<< orphan*/  reorder_timeout; void* lns_mode; void* send_seq; void* recv_seq; void* debug; int /*<<< orphan*/  ifname; int /*<<< orphan*/ * peer_cookie; int /*<<< orphan*/ * cookie; int /*<<< orphan*/  member_0; } ;
struct l2tp_session {int dummy; } ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_2__ {int (* session_create ) (struct net*,struct l2tp_tunnel*,void*,void*,struct l2tp_session_cfg*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPROTONOSUPPORT ; 
 size_t L2TP_ATTR_CONN_ID ; 
 size_t L2TP_ATTR_COOKIE ; 
 size_t L2TP_ATTR_DEBUG ; 
 size_t L2TP_ATTR_IFNAME ; 
 size_t L2TP_ATTR_L2SPEC_TYPE ; 
 size_t L2TP_ATTR_LNS_MODE ; 
 size_t L2TP_ATTR_PEER_COOKIE ; 
 size_t L2TP_ATTR_PEER_SESSION_ID ; 
 size_t L2TP_ATTR_PW_TYPE ; 
 size_t L2TP_ATTR_RECV_SEQ ; 
 size_t L2TP_ATTR_RECV_TIMEOUT ; 
 size_t L2TP_ATTR_SEND_SEQ ; 
 size_t L2TP_ATTR_SESSION_ID ; 
 int /*<<< orphan*/  L2TP_CMD_SESSION_CREATE ; 
 scalar_t__ L2TP_L2SPECTYPE_DEFAULT ; 
 scalar_t__ L2TP_L2SPECTYPE_NONE ; 
 size_t L2TP_PWTYPE_PPP ; 
 size_t __L2TP_PWTYPE_MAX ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 TYPE_1__** l2tp_nl_cmd_ops ; 
 int /*<<< orphan*/  l2tp_nl_family ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 int l2tp_session_notify (int /*<<< orphan*/ *,struct genl_info*,struct l2tp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 struct l2tp_tunnel* l2tp_tunnel_get (struct net*,void*) ; 
 struct l2tp_session* l2tp_tunnel_get_session (struct l2tp_tunnel*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_msecs (scalar_t__) ; 
 size_t nla_get_u16 (scalar_t__) ; 
 void* nla_get_u32 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 
 int nla_len (scalar_t__) ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int stub1 (struct net*,struct l2tp_tunnel*,void*,void*,struct l2tp_session_cfg*) ; 

__attribute__((used)) static int l2tp_nl_cmd_session_create(struct sk_buff *skb, struct genl_info *info)
{
	u32 tunnel_id = 0;
	u32 session_id;
	u32 peer_session_id;
	int ret = 0;
	struct l2tp_tunnel *tunnel;
	struct l2tp_session *session;
	struct l2tp_session_cfg cfg = { 0, };
	struct net *net = genl_info_net(info);

	if (!info->attrs[L2TP_ATTR_CONN_ID]) {
		ret = -EINVAL;
		goto out;
	}

	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);
	tunnel = l2tp_tunnel_get(net, tunnel_id);
	if (!tunnel) {
		ret = -ENODEV;
		goto out;
	}

	if (!info->attrs[L2TP_ATTR_SESSION_ID]) {
		ret = -EINVAL;
		goto out_tunnel;
	}
	session_id = nla_get_u32(info->attrs[L2TP_ATTR_SESSION_ID]);

	if (!info->attrs[L2TP_ATTR_PEER_SESSION_ID]) {
		ret = -EINVAL;
		goto out_tunnel;
	}
	peer_session_id = nla_get_u32(info->attrs[L2TP_ATTR_PEER_SESSION_ID]);

	if (!info->attrs[L2TP_ATTR_PW_TYPE]) {
		ret = -EINVAL;
		goto out_tunnel;
	}
	cfg.pw_type = nla_get_u16(info->attrs[L2TP_ATTR_PW_TYPE]);
	if (cfg.pw_type >= __L2TP_PWTYPE_MAX) {
		ret = -EINVAL;
		goto out_tunnel;
	}

	/* L2TPv2 only accepts PPP pseudo-wires */
	if (tunnel->version == 2 && cfg.pw_type != L2TP_PWTYPE_PPP) {
		ret = -EPROTONOSUPPORT;
		goto out_tunnel;
	}

	if (tunnel->version > 2) {
		if (info->attrs[L2TP_ATTR_L2SPEC_TYPE]) {
			cfg.l2specific_type = nla_get_u8(info->attrs[L2TP_ATTR_L2SPEC_TYPE]);
			if (cfg.l2specific_type != L2TP_L2SPECTYPE_DEFAULT &&
			    cfg.l2specific_type != L2TP_L2SPECTYPE_NONE) {
				ret = -EINVAL;
				goto out_tunnel;
			}
		} else {
			cfg.l2specific_type = L2TP_L2SPECTYPE_DEFAULT;
		}

		if (info->attrs[L2TP_ATTR_COOKIE]) {
			u16 len = nla_len(info->attrs[L2TP_ATTR_COOKIE]);
			if (len > 8) {
				ret = -EINVAL;
				goto out_tunnel;
			}
			cfg.cookie_len = len;
			memcpy(&cfg.cookie[0], nla_data(info->attrs[L2TP_ATTR_COOKIE]), len);
		}
		if (info->attrs[L2TP_ATTR_PEER_COOKIE]) {
			u16 len = nla_len(info->attrs[L2TP_ATTR_PEER_COOKIE]);
			if (len > 8) {
				ret = -EINVAL;
				goto out_tunnel;
			}
			cfg.peer_cookie_len = len;
			memcpy(&cfg.peer_cookie[0], nla_data(info->attrs[L2TP_ATTR_PEER_COOKIE]), len);
		}
		if (info->attrs[L2TP_ATTR_IFNAME])
			cfg.ifname = nla_data(info->attrs[L2TP_ATTR_IFNAME]);
	}

	if (info->attrs[L2TP_ATTR_DEBUG])
		cfg.debug = nla_get_u32(info->attrs[L2TP_ATTR_DEBUG]);

	if (info->attrs[L2TP_ATTR_RECV_SEQ])
		cfg.recv_seq = nla_get_u8(info->attrs[L2TP_ATTR_RECV_SEQ]);

	if (info->attrs[L2TP_ATTR_SEND_SEQ])
		cfg.send_seq = nla_get_u8(info->attrs[L2TP_ATTR_SEND_SEQ]);

	if (info->attrs[L2TP_ATTR_LNS_MODE])
		cfg.lns_mode = nla_get_u8(info->attrs[L2TP_ATTR_LNS_MODE]);

	if (info->attrs[L2TP_ATTR_RECV_TIMEOUT])
		cfg.reorder_timeout = nla_get_msecs(info->attrs[L2TP_ATTR_RECV_TIMEOUT]);

#ifdef CONFIG_MODULES
	if (l2tp_nl_cmd_ops[cfg.pw_type] == NULL) {
		genl_unlock();
		request_module("net-l2tp-type-%u", cfg.pw_type);
		genl_lock();
	}
#endif
	if ((l2tp_nl_cmd_ops[cfg.pw_type] == NULL) ||
	    (l2tp_nl_cmd_ops[cfg.pw_type]->session_create == NULL)) {
		ret = -EPROTONOSUPPORT;
		goto out_tunnel;
	}

	ret = l2tp_nl_cmd_ops[cfg.pw_type]->session_create(net, tunnel,
							   session_id,
							   peer_session_id,
							   &cfg);

	if (ret >= 0) {
		session = l2tp_tunnel_get_session(tunnel, session_id);
		if (session) {
			ret = l2tp_session_notify(&l2tp_nl_family, info, session,
						  L2TP_CMD_SESSION_CREATE);
			l2tp_session_dec_refcount(session);
		}
	}

out_tunnel:
	l2tp_tunnel_dec_refcount(tunnel);
out:
	return ret;
}
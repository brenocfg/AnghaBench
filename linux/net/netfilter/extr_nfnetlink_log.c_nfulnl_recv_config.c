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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  void* u_int16_t ;
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfulnl_msg_config_mode {int /*<<< orphan*/  copy_range; int /*<<< orphan*/  copy_mode; } ;
struct nfulnl_msg_config_cmd {int command; } ;
struct nfulnl_instance {scalar_t__ peer_portid; } ;
struct nfnl_log_net {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; int /*<<< orphan*/  res_id; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ERR (struct nfulnl_instance*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NFNL_SUBSYS_ULOG ; 
 size_t NFULA_CFG_CMD ; 
 size_t NFULA_CFG_FLAGS ; 
 size_t NFULA_CFG_MODE ; 
 size_t NFULA_CFG_NLBUFSIZ ; 
 size_t NFULA_CFG_QTHRESH ; 
 size_t NFULA_CFG_TIMEOUT ; 
#define  NFULNL_CFG_CMD_BIND 131 
#define  NFULNL_CFG_CMD_PF_BIND 130 
#define  NFULNL_CFG_CMD_PF_UNBIND 129 
#define  NFULNL_CFG_CMD_UNBIND 128 
 int NFULNL_CFG_F_CONNTRACK ; 
 int PTR_ERR (struct nfulnl_instance*) ; 
 struct nfulnl_instance* instance_create (struct net*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instance_destroy (struct nfnl_log_net*,struct nfulnl_instance*) ; 
 struct nfulnl_instance* instance_lookup_get (struct nfnl_log_net*,void*) ; 
 int /*<<< orphan*/  instance_put (struct nfulnl_instance*) ; 
 int nf_log_bind_pf (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_unbind_pf (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_ct_hook ; 
 int /*<<< orphan*/  nfnl_lock (int /*<<< orphan*/ ) ; 
 struct nfnl_log_net* nfnl_log_pernet (struct net*) ; 
 int /*<<< orphan*/  nfnl_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_logger ; 
 int /*<<< orphan*/  nfulnl_set_flags (struct nfulnl_instance*,int) ; 
 int /*<<< orphan*/  nfulnl_set_mode (struct nfulnl_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_nlbufsiz (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_qthresh (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_timeout (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfulnl_recv_config(struct net *net, struct sock *ctnl,
			      struct sk_buff *skb, const struct nlmsghdr *nlh,
			      const struct nlattr * const nfula[],
			      struct netlink_ext_ack *extack)
{
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int16_t group_num = ntohs(nfmsg->res_id);
	struct nfulnl_instance *inst;
	struct nfulnl_msg_config_cmd *cmd = NULL;
	struct nfnl_log_net *log = nfnl_log_pernet(net);
	int ret = 0;
	u16 flags = 0;

	if (nfula[NFULA_CFG_CMD]) {
		u_int8_t pf = nfmsg->nfgen_family;
		cmd = nla_data(nfula[NFULA_CFG_CMD]);

		/* Commands without queue context */
		switch (cmd->command) {
		case NFULNL_CFG_CMD_PF_BIND:
			return nf_log_bind_pf(net, pf, &nfulnl_logger);
		case NFULNL_CFG_CMD_PF_UNBIND:
			nf_log_unbind_pf(net, pf);
			return 0;
		}
	}

	inst = instance_lookup_get(log, group_num);
	if (inst && inst->peer_portid != NETLINK_CB(skb).portid) {
		ret = -EPERM;
		goto out_put;
	}

	/* Check if we support these flags in first place, dependencies should
	 * be there too not to break atomicity.
	 */
	if (nfula[NFULA_CFG_FLAGS]) {
		flags = ntohs(nla_get_be16(nfula[NFULA_CFG_FLAGS]));

		if ((flags & NFULNL_CFG_F_CONNTRACK) &&
		    !rcu_access_pointer(nfnl_ct_hook)) {
#ifdef CONFIG_MODULES
			nfnl_unlock(NFNL_SUBSYS_ULOG);
			request_module("ip_conntrack_netlink");
			nfnl_lock(NFNL_SUBSYS_ULOG);
			if (rcu_access_pointer(nfnl_ct_hook)) {
				ret = -EAGAIN;
				goto out_put;
			}
#endif
			ret = -EOPNOTSUPP;
			goto out_put;
		}
	}

	if (cmd != NULL) {
		switch (cmd->command) {
		case NFULNL_CFG_CMD_BIND:
			if (inst) {
				ret = -EBUSY;
				goto out_put;
			}

			inst = instance_create(net, group_num,
					       NETLINK_CB(skb).portid,
					       sk_user_ns(NETLINK_CB(skb).sk));
			if (IS_ERR(inst)) {
				ret = PTR_ERR(inst);
				goto out;
			}
			break;
		case NFULNL_CFG_CMD_UNBIND:
			if (!inst) {
				ret = -ENODEV;
				goto out;
			}

			instance_destroy(log, inst);
			goto out_put;
		default:
			ret = -ENOTSUPP;
			goto out_put;
		}
	} else if (!inst) {
		ret = -ENODEV;
		goto out;
	}

	if (nfula[NFULA_CFG_MODE]) {
		struct nfulnl_msg_config_mode *params =
			nla_data(nfula[NFULA_CFG_MODE]);

		nfulnl_set_mode(inst, params->copy_mode,
				ntohl(params->copy_range));
	}

	if (nfula[NFULA_CFG_TIMEOUT]) {
		__be32 timeout = nla_get_be32(nfula[NFULA_CFG_TIMEOUT]);

		nfulnl_set_timeout(inst, ntohl(timeout));
	}

	if (nfula[NFULA_CFG_NLBUFSIZ]) {
		__be32 nlbufsiz = nla_get_be32(nfula[NFULA_CFG_NLBUFSIZ]);

		nfulnl_set_nlbufsiz(inst, ntohl(nlbufsiz));
	}

	if (nfula[NFULA_CFG_QTHRESH]) {
		__be32 qthresh = nla_get_be32(nfula[NFULA_CFG_QTHRESH]);

		nfulnl_set_qthresh(inst, ntohl(qthresh));
	}

	if (nfula[NFULA_CFG_FLAGS])
		nfulnl_set_flags(inst, flags);

out_put:
	instance_put(inst);
out:
	return ret;
}
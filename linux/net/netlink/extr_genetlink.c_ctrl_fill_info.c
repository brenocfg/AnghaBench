#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_ops {int flags; int cmd; scalar_t__ doit; scalar_t__ dumpit; } ;
struct genl_multicast_group {int /*<<< orphan*/  name; } ;
struct genl_family {int version; int hdrsize; int maxattr; int n_ops; int n_mcgrps; int mcgrp_offset; struct genl_multicast_group* mcgrps; scalar_t__ policy; struct genl_ops* ops; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_ATTR_FAMILY_ID ; 
 int /*<<< orphan*/  CTRL_ATTR_FAMILY_NAME ; 
 int /*<<< orphan*/  CTRL_ATTR_HDRSIZE ; 
 int /*<<< orphan*/  CTRL_ATTR_MAXATTR ; 
 int CTRL_ATTR_MCAST_GROUPS ; 
 int /*<<< orphan*/  CTRL_ATTR_MCAST_GRP_ID ; 
 int /*<<< orphan*/  CTRL_ATTR_MCAST_GRP_NAME ; 
 int CTRL_ATTR_OPS ; 
 int /*<<< orphan*/  CTRL_ATTR_OP_FLAGS ; 
 int /*<<< orphan*/  CTRL_ATTR_OP_ID ; 
 int /*<<< orphan*/  CTRL_ATTR_VERSION ; 
 int EMSGSIZE ; 
 int GENL_CMD_CAP_DO ; 
 int GENL_CMD_CAP_DUMP ; 
 int GENL_CMD_CAP_HASPOL ; 
 int /*<<< orphan*/  genl_ctrl ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctrl_fill_info(const struct genl_family *family, u32 portid, u32 seq,
			  u32 flags, struct sk_buff *skb, u8 cmd)
{
	void *hdr;

	hdr = genlmsg_put(skb, portid, seq, &genl_ctrl, flags, cmd);
	if (hdr == NULL)
		return -1;

	if (nla_put_string(skb, CTRL_ATTR_FAMILY_NAME, family->name) ||
	    nla_put_u16(skb, CTRL_ATTR_FAMILY_ID, family->id) ||
	    nla_put_u32(skb, CTRL_ATTR_VERSION, family->version) ||
	    nla_put_u32(skb, CTRL_ATTR_HDRSIZE, family->hdrsize) ||
	    nla_put_u32(skb, CTRL_ATTR_MAXATTR, family->maxattr))
		goto nla_put_failure;

	if (family->n_ops) {
		struct nlattr *nla_ops;
		int i;

		nla_ops = nla_nest_start_noflag(skb, CTRL_ATTR_OPS);
		if (nla_ops == NULL)
			goto nla_put_failure;

		for (i = 0; i < family->n_ops; i++) {
			struct nlattr *nest;
			const struct genl_ops *ops = &family->ops[i];
			u32 op_flags = ops->flags;

			if (ops->dumpit)
				op_flags |= GENL_CMD_CAP_DUMP;
			if (ops->doit)
				op_flags |= GENL_CMD_CAP_DO;
			if (family->policy)
				op_flags |= GENL_CMD_CAP_HASPOL;

			nest = nla_nest_start_noflag(skb, i + 1);
			if (nest == NULL)
				goto nla_put_failure;

			if (nla_put_u32(skb, CTRL_ATTR_OP_ID, ops->cmd) ||
			    nla_put_u32(skb, CTRL_ATTR_OP_FLAGS, op_flags))
				goto nla_put_failure;

			nla_nest_end(skb, nest);
		}

		nla_nest_end(skb, nla_ops);
	}

	if (family->n_mcgrps) {
		struct nlattr *nla_grps;
		int i;

		nla_grps = nla_nest_start_noflag(skb, CTRL_ATTR_MCAST_GROUPS);
		if (nla_grps == NULL)
			goto nla_put_failure;

		for (i = 0; i < family->n_mcgrps; i++) {
			struct nlattr *nest;
			const struct genl_multicast_group *grp;

			grp = &family->mcgrps[i];

			nest = nla_nest_start_noflag(skb, i + 1);
			if (nest == NULL)
				goto nla_put_failure;

			if (nla_put_u32(skb, CTRL_ATTR_MCAST_GRP_ID,
					family->mcgrp_offset + i) ||
			    nla_put_string(skb, CTRL_ATTR_MCAST_GRP_NAME,
					   grp->name))
				goto nla_put_failure;

			nla_nest_end(skb, nest);
		}
		nla_nest_end(skb, nla_grps);
	}

	genlmsg_end(skb, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -EMSGSIZE;
}
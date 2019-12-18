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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_nl_compat_msg {int dummy; } ;
struct tipc_nl_compat_cmd_dump {int /*<<< orphan*/  format; int /*<<< orphan*/  dumpit; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_REF ; 
 int /*<<< orphan*/  TIPC_NL_PUBL_GET ; 
 int __tipc_nl_compat_dumpit (struct tipc_nl_compat_cmd_dump*,struct tipc_nl_compat_msg*,struct sk_buff*) ; 
 int /*<<< orphan*/  __tipc_nl_compat_publ_dump ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 int /*<<< orphan*/  tipc_nl_publ_dump ; 

__attribute__((used)) static int tipc_nl_compat_publ_dump(struct tipc_nl_compat_msg *msg, u32 sock)
{
	int err;
	void *hdr;
	struct nlattr *nest;
	struct sk_buff *args;
	struct tipc_nl_compat_cmd_dump dump;

	args = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!args)
		return -ENOMEM;

	hdr = genlmsg_put(args, 0, 0, &tipc_genl_family, NLM_F_MULTI,
			  TIPC_NL_PUBL_GET);
	if (!hdr) {
		kfree_skb(args);
		return -EMSGSIZE;
	}

	nest = nla_nest_start_noflag(args, TIPC_NLA_SOCK);
	if (!nest) {
		kfree_skb(args);
		return -EMSGSIZE;
	}

	if (nla_put_u32(args, TIPC_NLA_SOCK_REF, sock)) {
		kfree_skb(args);
		return -EMSGSIZE;
	}

	nla_nest_end(args, nest);
	genlmsg_end(args, hdr);

	dump.dumpit = tipc_nl_publ_dump;
	dump.format = __tipc_nl_compat_publ_dump;

	err = __tipc_nl_compat_dumpit(&dump, msg, args);

	kfree_skb(args);

	return err;
}
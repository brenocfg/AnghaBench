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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  NLMSG_DONE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 size_t SMC_PNETID_NAME ; 
 int /*<<< orphan*/  _smc_pnet_dump (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_pnet_get(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct sk_buff *msg;
	void *hdr;

	if (!info->attrs[SMC_PNETID_NAME])
		return -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	_smc_pnet_dump(net, msg, info->snd_portid, info->snd_seq,
		       nla_data(info->attrs[SMC_PNETID_NAME]), 0);

	/* finish multi part message and send it */
	hdr = nlmsg_put(msg, info->snd_portid, info->snd_seq, NLMSG_DONE, 0,
			NLM_F_MULTI);
	if (!hdr) {
		nlmsg_free(msg);
		return -EMSGSIZE;
	}
	return genlmsg_reply(msg, info);
}
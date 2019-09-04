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
struct genl_info {int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  L2TP_CMD_NOOP ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_nl_family ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_nl_cmd_noop(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	void *hdr;
	int ret = -ENOBUFS;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto out;
	}

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &l2tp_nl_family, 0, L2TP_CMD_NOOP);
	if (!hdr) {
		ret = -EMSGSIZE;
		goto err_out;
	}

	genlmsg_end(msg, hdr);

	return genlmsg_unicast(genl_info_net(info), msg, info->snd_portid);

err_out:
	nlmsg_free(msg);

out:
	return ret;
}
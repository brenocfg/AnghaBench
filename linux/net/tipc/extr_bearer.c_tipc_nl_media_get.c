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
struct tipc_nl_msg {int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; struct sk_buff* skb; } ;
struct tipc_media {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER_MAX ; 
 size_t TIPC_NLA_MEDIA ; 
 int /*<<< orphan*/  TIPC_NLA_MEDIA_MAX ; 
 size_t TIPC_NLA_MEDIA_NAME ; 
 int __tipc_nl_add_media (struct tipc_nl_msg*,struct tipc_media*,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 char* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct tipc_media* tipc_media_find (char*) ; 
 int /*<<< orphan*/  tipc_nl_media_policy ; 

int tipc_nl_media_get(struct sk_buff *skb, struct genl_info *info)
{
	int err;
	char *name;
	struct tipc_nl_msg msg;
	struct tipc_media *media;
	struct sk_buff *rep;
	struct nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];

	if (!info->attrs[TIPC_NLA_MEDIA])
		return -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_MEDIA_MAX,
					  info->attrs[TIPC_NLA_MEDIA],
					  tipc_nl_media_policy, info->extack);
	if (err)
		return err;

	if (!attrs[TIPC_NLA_MEDIA_NAME])
		return -EINVAL;
	name = nla_data(attrs[TIPC_NLA_MEDIA_NAME]);

	rep = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!rep)
		return -ENOMEM;

	msg.skb = rep;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	rtnl_lock();
	media = tipc_media_find(name);
	if (!media) {
		err = -EINVAL;
		goto err_out;
	}

	err = __tipc_nl_add_media(&msg, media, 0);
	if (err)
		goto err_out;
	rtnl_unlock();

	return genlmsg_reply(rep, info);
err_out:
	rtnl_unlock();
	nlmsg_free(rep);

	return err;
}
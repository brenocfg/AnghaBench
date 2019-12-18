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
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct tipc_media {scalar_t__ type_id; int /*<<< orphan*/  mtu; int /*<<< orphan*/  window; int /*<<< orphan*/  tolerance; int /*<<< orphan*/  priority; int /*<<< orphan*/  name; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ TIPC_MEDIA_TYPE_UDP ; 
 int /*<<< orphan*/  TIPC_NLA_MEDIA ; 
 int /*<<< orphan*/  TIPC_NLA_MEDIA_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_MEDIA_PROP ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_MTU ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_PRIO ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_TOL ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_WIN ; 
 int /*<<< orphan*/  TIPC_NL_MEDIA_GET ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_add_media(struct tipc_nl_msg *msg,
			       struct tipc_media *media, int nlflags)
{
	void *hdr;
	struct nlattr *attrs;
	struct nlattr *prop;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  nlflags, TIPC_NL_MEDIA_GET);
	if (!hdr)
		return -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MEDIA);
	if (!attrs)
		goto msg_full;

	if (nla_put_string(msg->skb, TIPC_NLA_MEDIA_NAME, media->name))
		goto attr_msg_full;

	prop = nla_nest_start_noflag(msg->skb, TIPC_NLA_MEDIA_PROP);
	if (!prop)
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_PRIO, media->priority))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_TOL, media->tolerance))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_WIN, media->window))
		goto prop_msg_full;
	if (media->type_id == TIPC_MEDIA_TYPE_UDP)
		if (nla_put_u32(msg->skb, TIPC_NLA_PROP_MTU, media->mtu))
			goto prop_msg_full;

	nla_nest_end(msg->skb, prop);
	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	return 0;

prop_msg_full:
	nla_nest_cancel(msg->skb, prop);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}
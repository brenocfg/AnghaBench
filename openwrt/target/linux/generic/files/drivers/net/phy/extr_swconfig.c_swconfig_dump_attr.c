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
struct switch_attr {int type; scalar_t__ description; scalar_t__ name; } ;
struct swconfig_callback {int* args; struct sk_buff* msg; struct genl_info* info; } ;
struct sk_buff {int len; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_DESCRIPTION ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_ID ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_NAME ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_TYPE ; 
 int /*<<< orphan*/  SWITCH_CMD_NEW_ATTR ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  switch_fam ; 

__attribute__((used)) static int
swconfig_dump_attr(struct swconfig_callback *cb, void *arg)
{
	struct switch_attr *op = arg;
	struct genl_info *info = cb->info;
	struct sk_buff *msg = cb->msg;
	int id = cb->args[0];
	void *hdr;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq, &switch_fam,
			NLM_F_MULTI, SWITCH_CMD_NEW_ATTR);
	if (IS_ERR(hdr))
		return -1;

	if (nla_put_u32(msg, SWITCH_ATTR_OP_ID, id))
		goto nla_put_failure;
	if (nla_put_u32(msg, SWITCH_ATTR_OP_TYPE, op->type))
		goto nla_put_failure;
	if (nla_put_string(msg, SWITCH_ATTR_OP_NAME, op->name))
		goto nla_put_failure;
	if (op->description)
		if (nla_put_string(msg, SWITCH_ATTR_OP_DESCRIPTION,
			op->description))
			goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return msg->len;
nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}
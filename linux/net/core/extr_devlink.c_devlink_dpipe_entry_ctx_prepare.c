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
struct devlink_dpipe_dump_ctx {int /*<<< orphan*/  skb; int /*<<< orphan*/  nest; TYPE_1__* info; int /*<<< orphan*/  hdr; int /*<<< orphan*/  cmd; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {struct devlink** user_ptr; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRIES ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int devlink_dpipe_send_and_alloc_skb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_put_handle (int /*<<< orphan*/ ,struct devlink*) ; 
 int /*<<< orphan*/  genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (int /*<<< orphan*/ ) ; 

int devlink_dpipe_entry_ctx_prepare(struct devlink_dpipe_dump_ctx *dump_ctx)
{
	struct devlink *devlink;
	int err;

	err = devlink_dpipe_send_and_alloc_skb(&dump_ctx->skb,
					       dump_ctx->info);
	if (err)
		return err;

	dump_ctx->hdr = genlmsg_put(dump_ctx->skb,
				    dump_ctx->info->snd_portid,
				    dump_ctx->info->snd_seq,
				    &devlink_nl_family, NLM_F_MULTI,
				    dump_ctx->cmd);
	if (!dump_ctx->hdr)
		goto nla_put_failure;

	devlink = dump_ctx->info->user_ptr[0];
	if (devlink_nl_put_handle(dump_ctx->skb, devlink))
		goto nla_put_failure;
	dump_ctx->nest = nla_nest_start_noflag(dump_ctx->skb,
					       DEVLINK_ATTR_DPIPE_ENTRIES);
	if (!dump_ctx->nest)
		goto nla_put_failure;
	return 0;

nla_put_failure:
	nlmsg_free(dump_ctx->skb);
	return -EMSGSIZE;
}
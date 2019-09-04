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
struct devlink_dpipe_dump_ctx {int /*<<< orphan*/  hdr; int /*<<< orphan*/  skb; int /*<<< orphan*/  nest; } ;

/* Variables and functions */
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int devlink_dpipe_entry_ctx_close(struct devlink_dpipe_dump_ctx *dump_ctx)
{
	nla_nest_end(dump_ctx->skb, dump_ctx->nest);
	genlmsg_end(dump_ctx->skb, dump_ctx->hdr);
	return 0;
}
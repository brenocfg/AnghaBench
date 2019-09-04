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
struct mp_cmd_ctx {int success; struct MPContext* mpctx; } ;
struct MPContext {TYPE_1__* demuxer; } ;
struct TYPE_2__ {int /*<<< orphan*/  extended_ctrls; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CTRL_TV_LAST_CHAN ; 
 int /*<<< orphan*/  demux_stream_control (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmd_tv_last_channel(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    if (!mpctx->demuxer || !mpctx->demuxer->extended_ctrls) {
        cmd->success = false;
        return;
    }

    demux_stream_control(mpctx->demuxer, STREAM_CTRL_TV_LAST_CHAN, NULL);
}
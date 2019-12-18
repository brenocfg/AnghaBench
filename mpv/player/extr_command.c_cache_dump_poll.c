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
struct mp_cmd_ctx {int success; TYPE_1__* abort; } ;
struct command_ctx {struct mp_cmd_ctx* cache_dump_cmd; } ;
struct MPContext {int demuxer; struct command_ctx* command_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_ERR ; 
 int /*<<< orphan*/  MSGL_INFO ; 
 int /*<<< orphan*/  assert (int) ; 
 int demux_cache_dump_get_status (int) ; 
 int /*<<< orphan*/  demux_cache_dump_set (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cancel_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cmd_ctx_complete (struct mp_cmd_ctx*) ; 
 int /*<<< orphan*/  mp_cmd_msg (struct mp_cmd_ctx*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cache_dump_poll(struct MPContext *mpctx)
{
    struct command_ctx *ctx = mpctx->command_ctx;
    struct mp_cmd_ctx *cmd = ctx->cache_dump_cmd;

    if (!cmd)
        return;

    // Can't close demuxer without stopping dumping.
    assert(mpctx->demuxer);

    if (mp_cancel_test(cmd->abort->cancel)) {
        // Synchronous abort. In particular, the dump command shall not report
        // completion to the user before the dump target file was closed.
        demux_cache_dump_set(mpctx->demuxer, 0, 0, NULL);
        assert(demux_cache_dump_get_status(mpctx->demuxer) <= 0);
    }

    int status = demux_cache_dump_get_status(mpctx->demuxer);
    if (status <= 0) {
        if (status < 0) {
            mp_cmd_msg(cmd, MSGL_ERR, "Cache dumping stopped due to error.");
            cmd->success = false;
        } else {
            mp_cmd_msg(cmd, MSGL_INFO, "Cache dumping successfully ended.");
            cmd->success = true;
        }
        ctx->cache_dump_cmd = NULL;
        mp_cmd_ctx_complete(cmd);
    }
}
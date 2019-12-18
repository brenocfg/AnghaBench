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
struct mp_cmd_ctx {int success; struct MPContext* mpctx; } ;
struct command_ctx {struct mp_cmd_ctx* cache_dump_cmd; } ;
struct MPContext {int /*<<< orphan*/  demuxer; struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_ERR ; 
 int /*<<< orphan*/  MSGL_INFO ; 
 int /*<<< orphan*/  cache_dump_poll (struct MPContext*) ; 
 int /*<<< orphan*/  demux_cache_dump_set (int /*<<< orphan*/ ,double,double,char*) ; 
 int /*<<< orphan*/  mp_abort_cache_dumping (struct MPContext*) ; 
 int /*<<< orphan*/  mp_cmd_ctx_complete (struct mp_cmd_ctx*) ; 
 int /*<<< orphan*/  mp_cmd_msg (struct mp_cmd_ctx*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void run_dump_cmd(struct mp_cmd_ctx *cmd, double start, double end,
                         char *filename)
{
    struct MPContext *mpctx = cmd->mpctx;
    struct command_ctx *ctx = mpctx->command_ctx;

    mp_abort_cache_dumping(mpctx);

    if (!mpctx->demuxer) {
        mp_cmd_msg(cmd, MSGL_ERR, "No demuxer open.");
        cmd->success = false;
        mp_cmd_ctx_complete(cmd);
        return;
    }

    mp_cmd_msg(cmd, MSGL_INFO, "Cache dumping started.");

    if (!demux_cache_dump_set(mpctx->demuxer, start, end, filename)) {
        mp_cmd_msg(cmd, MSGL_INFO, "Cache dumping stopped.");
        mp_cmd_ctx_complete(cmd);
        return;
    }

    ctx->cache_dump_cmd = cmd;
    cache_dump_poll(mpctx);
}
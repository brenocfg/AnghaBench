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
struct mp_cmd_ctx {struct MPContext* mpctx; } ;
struct MPContext {scalar_t__ demuxer; } ;

/* Variables and functions */
 int /*<<< orphan*/  demux_flush (scalar_t__) ; 
 int /*<<< orphan*/  reset_audio_state (struct MPContext*) ; 
 int /*<<< orphan*/  reset_video_state (struct MPContext*) ; 

__attribute__((used)) static void cmd_drop_buffers(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    reset_audio_state(mpctx);
    reset_video_state(mpctx);

    if (mpctx->demuxer)
        demux_flush(mpctx->demuxer);
}
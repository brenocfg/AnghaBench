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
struct command_ctx {int is_idle; void* marked_pts; void* last_seek_pts; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int MPV_EVENT_END_FILE ; 
 int MPV_EVENT_FILE_LOADED ; 
 int MPV_EVENT_IDLE ; 
 int MPV_EVENT_START_FILE ; 
 void* MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  OSD_BAR_SEEK ; 
 int /*<<< orphan*/  set_osd_bar_chapters (struct MPContext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void command_event(struct MPContext *mpctx, int event, void *arg)
{
    struct command_ctx *ctx = mpctx->command_ctx;

    if (event == MPV_EVENT_START_FILE) {
        ctx->last_seek_pts = MP_NOPTS_VALUE;
        ctx->marked_pts = MP_NOPTS_VALUE;
    }

    if (event == MPV_EVENT_IDLE)
        ctx->is_idle = true;
    if (event == MPV_EVENT_START_FILE)
        ctx->is_idle = false;
    if (event == MPV_EVENT_END_FILE || event == MPV_EVENT_FILE_LOADED) {
        // Update chapters - does nothing if something else is visible.
        set_osd_bar_chapters(mpctx, OSD_BAR_SEEK);
    }
}
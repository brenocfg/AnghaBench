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
struct MPContext {scalar_t__ stop_play; int /*<<< orphan*/  playlist; } ;

/* Variables and functions */
 scalar_t__ PT_QUIT ; 
 scalar_t__ PT_STOP ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  playlist_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_stop(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    playlist_clear(mpctx->playlist);
    if (mpctx->stop_play != PT_QUIT)
        mpctx->stop_play = PT_STOP;
    mp_wakeup_core(mpctx);
}
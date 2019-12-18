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
struct mp_cmd_ctx {scalar_t__ bar_osd; scalar_t__ msg_osd; struct MPContext* mpctx; } ;
struct MPContext {int add_osd_seek_info; int osd_force_update; } ;

/* Variables and functions */
 int OSD_SEEK_INFO_BAR ; 
 int OSD_SEEK_INFO_TEXT ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 

__attribute__((used)) static void cmd_show_progress(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    mpctx->add_osd_seek_info |=
            (cmd->msg_osd ? OSD_SEEK_INFO_TEXT : 0) |
            (cmd->bar_osd ? OSD_SEEK_INFO_BAR : 0);
    mpctx->osd_force_update = true;
    mp_wakeup_core(mpctx);
}
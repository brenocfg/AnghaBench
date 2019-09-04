#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int dummy; } ;
struct mp_cmd_ctx {int success; int on_osd; TYPE_2__* args; scalar_t__ priv; struct MPContext* mpctx; } ;
struct MPContext {int /*<<< orphan*/  add_osd_seek_info; } ;
struct TYPE_3__ {int i; } ;
struct TYPE_4__ {TYPE_1__ v; } ;

/* Variables and functions */
 int MP_ON_OSD_MSG ; 
 int /*<<< orphan*/  OSD_SEEK_INFO_CURRENT_FILE ; 
 struct playlist_entry* mp_next_file (struct MPContext*,int,int,int) ; 
 int /*<<< orphan*/  mp_set_playlist_entry (struct MPContext*,struct playlist_entry*) ; 

__attribute__((used)) static void cmd_playlist_next_prev(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    int dir = *(int *)cmd->priv;
    int force = cmd->args[0].v.i;

    struct playlist_entry *e = mp_next_file(mpctx, dir, force, true);
    if (!e && !force) {
        cmd->success = false;
        return;
    }

    mp_set_playlist_entry(mpctx, e);
    if (cmd->on_osd & MP_ON_OSD_MSG)
        mpctx->add_osd_seek_info |= OSD_SEEK_INFO_CURRENT_FILE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int dummy; } ;
struct mp_cmd_ctx {int success; TYPE_2__* args; struct MPContext* mpctx; } ;
struct MPContext {TYPE_3__* playlist; scalar_t__ stop_play; } ;
struct TYPE_7__ {struct playlist_entry* current; } ;
struct TYPE_5__ {scalar_t__ i; } ;
struct TYPE_6__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_EVENT_CHANGE_PLAYLIST ; 
 scalar_t__ PT_NEXT_ENTRY ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 struct playlist_entry* playlist_entry_from_index (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  playlist_remove (TYPE_3__*,struct playlist_entry*) ; 

__attribute__((used)) static void cmd_playlist_remove(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    struct playlist_entry *e = playlist_entry_from_index(mpctx->playlist,
                                                         cmd->args[0].v.i);
    if (cmd->args[0].v.i < 0)
        e = mpctx->playlist->current;
    if (!e) {
        cmd->success = false;
        return;
    }

    // Can't play a removed entry
    if (mpctx->playlist->current == e && !mpctx->stop_play)
        mpctx->stop_play = PT_NEXT_ENTRY;
    playlist_remove(mpctx->playlist, e);
    mp_notify(mpctx, MP_EVENT_CHANGE_PLAYLIST, NULL);
    mp_wakeup_core(mpctx);
}
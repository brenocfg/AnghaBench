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
struct mp_cmd_ctx {int success; TYPE_2__* args; struct MPContext* mpctx; } ;
struct MPContext {int /*<<< orphan*/  playlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  i; } ;
struct TYPE_4__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_EVENT_CHANGE_PLAYLIST ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct playlist_entry* playlist_entry_from_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_move (int /*<<< orphan*/ ,struct playlist_entry*,struct playlist_entry*) ; 

__attribute__((used)) static void cmd_playlist_move(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    struct playlist_entry *e1 = playlist_entry_from_index(mpctx->playlist,
                                                          cmd->args[0].v.i);
    struct playlist_entry *e2 = playlist_entry_from_index(mpctx->playlist,
                                                          cmd->args[1].v.i);
    if (!e1) {
        cmd->success = false;
        return;
    }

    playlist_move(mpctx->playlist, e1, e2);
    mp_notify(mpctx, MP_EVENT_CHANGE_PLAYLIST, NULL);
}
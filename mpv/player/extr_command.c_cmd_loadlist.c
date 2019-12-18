#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int dummy; } ;
struct playlist {struct playlist_entry* current; } ;
struct mp_cmd_ctx {int success; TYPE_3__* abort; TYPE_2__* args; struct MPContext* mpctx; } ;
struct MPContext {TYPE_4__* playlist; int /*<<< orphan*/  global; } ;
struct TYPE_9__ {struct playlist_entry* first; } ;
struct TYPE_8__ {int /*<<< orphan*/  cancel; } ;
struct TYPE_6__ {char* s; int i; } ;
struct TYPE_7__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,char*) ; 
 int /*<<< orphan*/  MP_EVENT_CHANGE_PLAYLIST ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_set_playlist_entry (struct MPContext*,struct playlist_entry*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  playlist_append_entries (TYPE_4__*,struct playlist*) ; 
 int /*<<< orphan*/  playlist_clear (TYPE_4__*) ; 
 struct playlist* playlist_parse_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_playlist (struct MPContext*,struct playlist*) ; 
 int /*<<< orphan*/  talloc_free (struct playlist*) ; 

__attribute__((used)) static void cmd_loadlist(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    char *filename = cmd->args[0].v.s;
    bool append = cmd->args[1].v.i;

    struct playlist *pl = playlist_parse_file(filename, cmd->abort->cancel,
                                              mpctx->global);
    if (pl) {
        prepare_playlist(mpctx, pl);
        struct playlist_entry *new = pl->current;
        if (!append)
            playlist_clear(mpctx->playlist);
        playlist_append_entries(mpctx->playlist, pl);
        talloc_free(pl);

        if (!append && mpctx->playlist->first)
            mp_set_playlist_entry(mpctx, new ? new : mpctx->playlist->first);

        mp_notify(mpctx, MP_EVENT_CHANGE_PLAYLIST, NULL);
        mp_wakeup_core(mpctx);
    } else {
        MP_ERR(mpctx, "Unable to load playlist %s.\n", filename);
        cmd->success = false;
    }
}
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
struct playlist_entry {struct playlist_entry* next; } ;
struct mp_cmd_ctx {struct MPContext* mpctx; } ;
struct MPContext {TYPE_1__* playlist; } ;
struct TYPE_2__ {struct playlist_entry* current; struct playlist_entry* first; scalar_t__ current_was_replaced; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_EVENT_CHANGE_PLAYLIST ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  playlist_remove (TYPE_1__*,struct playlist_entry*) ; 

__attribute__((used)) static void cmd_playlist_clear(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    // Supposed to clear the playlist, except the currently played item.
    if (mpctx->playlist->current_was_replaced)
        mpctx->playlist->current = NULL;
    while (mpctx->playlist->first) {
        struct playlist_entry *e = mpctx->playlist->first;
        if (e == mpctx->playlist->current) {
            e = e->next;
            if (!e)
                break;
        }
        playlist_remove(mpctx->playlist, e);
    }
    mp_notify(mpctx, MP_EVENT_CHANGE_PLAYLIST, NULL);
    mp_wakeup_core(mpctx);
}
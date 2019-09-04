#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int /*<<< orphan*/  filename; } ;
struct playlist {struct playlist_entry* current; scalar_t__ first; } ;
struct MPContext {TYPE_1__* playlist; } ;
struct TYPE_3__ {struct playlist_entry* current; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*) ; 
 int /*<<< orphan*/  playlist_add_redirect (struct playlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_remove (TYPE_1__*,struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_transfer_entries (TYPE_1__*,struct playlist*) ; 
 int /*<<< orphan*/  prepare_playlist (struct MPContext*,struct playlist*) ; 

__attribute__((used)) static void transfer_playlist(struct MPContext *mpctx, struct playlist *pl)
{
    if (pl->first) {
        prepare_playlist(mpctx, pl);
        struct playlist_entry *new = pl->current;
        if (mpctx->playlist->current)
            playlist_add_redirect(pl, mpctx->playlist->current->filename);
        playlist_transfer_entries(mpctx->playlist, pl);
        // current entry is replaced
        if (mpctx->playlist->current)
            playlist_remove(mpctx->playlist, mpctx->playlist->current);
        if (new)
            mpctx->playlist->current = new;
    } else {
        MP_WARN(mpctx, "Empty playlist!\n");
    }
}
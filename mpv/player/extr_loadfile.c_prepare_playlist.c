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
struct playlist {int /*<<< orphan*/ * first; int /*<<< orphan*/ * current; } ;
struct MPOpts {scalar_t__ playlist_pos; scalar_t__ merge_files; scalar_t__ shuffle; } ;
struct MPContext {struct MPOpts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  merge_playlist_files (struct playlist*) ; 
 int /*<<< orphan*/ * mp_check_playlist_resume (struct MPContext*,struct playlist*) ; 
 int /*<<< orphan*/ * playlist_entry_from_index (struct playlist*,scalar_t__) ; 
 int /*<<< orphan*/  playlist_shuffle (struct playlist*) ; 

void prepare_playlist(struct MPContext *mpctx, struct playlist *pl)
{
    struct MPOpts *opts = mpctx->opts;

    pl->current = NULL;

    if (opts->playlist_pos >= 0)
        pl->current = playlist_entry_from_index(pl, opts->playlist_pos);

    if (opts->shuffle)
        playlist_shuffle(pl);

    if (opts->merge_files)
        merge_playlist_files(pl);

    if (!pl->current)
        pl->current = mp_check_playlist_resume(mpctx, pl);

    if (!pl->current)
        pl->current = pl->first;
}
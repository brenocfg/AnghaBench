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
struct playlist_entry {int /*<<< orphan*/  filename; struct playlist_entry* next; } ;
struct playlist {struct playlist_entry* first; } ;
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  position_resume; } ;

/* Variables and functions */
 char* mp_get_playback_resume_config_filename (struct MPContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_path_exists (char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

struct playlist_entry *mp_check_playlist_resume(struct MPContext *mpctx,
                                                struct playlist *playlist)
{
    if (!mpctx->opts->position_resume)
        return NULL;
    for (struct playlist_entry *e = playlist->first; e; e = e->next) {
        char *conf = mp_get_playback_resume_config_filename(mpctx, e->filename);
        bool exists = conf && mp_path_exists(conf);
        talloc_free(conf);
        if (exists)
            return e;
    }
    return NULL;
}